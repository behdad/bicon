#include "bjoining_vis2cuni.h"

#include <stdlib.h>
#include <string.h>

#define DELETE 0xFFFF

#define ISOLATED 0
#define FINAL 1
#define INITIAL 2
#define MEDIAL 3

typedef struct
{
  unichar code;			/* should be the first field */
  int num;
  unichar shape[4];
}
con_shape_type;

static con_shape_type con_shape[] = {
#include "shape.i"
};

#define con_size array_size(con_shape)
#define con_code(i) con_shape[i].code

typedef struct
{
  unichar code;			/* should be the first field */
  int ty;			/* 1 = joins, -1 = ambigous */
}
join_table_type;

static int tables_init = 0;
static join_table_type *join_tab[2];
static int join_c[2];

static int
comp_unichars (CONST void *p, CONST void *q)
{
  return *(unichar *) p - *(unichar *) q;
}

static void
init_tables ()
{
  int i;
  int count[5] = { 0, 0, 0, 0, 0 };

  if (tables_init)
    return;

  qsort (con_shape, con_size, sizeof con_shape[0], comp_unichars);

  join_c[0] = join_c[1] = 0;
  for (i = 0; i < con_size; i++)
    count[con_shape[i].num]++;
  join_tab[0] =
    malloc ((3 * count[4] + 2 * count[2]) * sizeof join_tab[0][0]);
  join_tab[1] = malloc (3 * count[4] * sizeof join_tab[1][0]);
  for (i = 0; i < con_size; i++)
    {
      con_shape_type *p = con_shape + i;
      if (p->num >= 2)
	{
	  join_tab[0][join_c[0]].code = p->code;
	  join_tab[0][join_c[0]++].ty = -1;
	  if (p->shape[1] != DELETE && p->shape[1] != p->code)
	    {
	      join_tab[0][join_c[0]].code = p->shape[1];
	      join_tab[0][join_c[0]++].ty = 1;
	    }
	  if (p->num == 4)
	    {
	      if (p->shape[2] != DELETE && p->shape[2] != p->code)
		{
		  join_tab[1][join_c[1]].code = p->shape[2];
		  join_tab[1][join_c[1]++].ty = 1;
		}
	      if (p->shape[3] != DELETE && p->shape[3] != p->code)
		{
		  join_tab[0][join_c[0]].code = p->shape[3];
		  join_tab[0][join_c[0]++].ty = 1;
		  join_tab[1][join_c[1]].code = p->shape[3];
		  join_tab[1][join_c[1]++].ty = 1;
		}
	      join_tab[1][join_c[1]].code = p->code;
	      join_tab[1][join_c[1]++].ty = -1;
	    }
	}
    }
  for (i = 0; i < 2; i++)
    qsort (join_tab[i], join_c[i], sizeof join_tab[i][0], comp_unichars);

  tables_init = 1;
}

int
join_type (unichar w, int next)
{
  int *p;

  if (!tables_init)
    init_tables ();
  p =
    (int *) bsearch (&w, join_tab[next], join_c[next],
		     sizeof join_tab[next][0], comp_unichars);
  if (p)
    return *p;
  return 0;
}

con_shape_type *
find_con_shape (unichar w)
{
  if (!tables_init)
    init_tables ();

  return bsearch (&w, con_shape, con_size, sizeof con_shape[0],
		  comp_unichars);
}

#undef con_size
#undef con_code

typedef struct
{
  unichar first, second, lig;
}
arablig_type;

arablig_type arablig_tab[] = {
#include "arablig.i"
};

#define arablig_size array_size(arablig_tab)
unichar
arablig (unichar first, unichar second)
{
  int i;

  for (i = 0; i < arablig_size; ++i)
    {
      if (first == arablig_tab[i].first && second == arablig_tab[i].second)
	{
	  return arablig_tab[i].lig;
	}
    }
  return NOLIG;
}

#undef arablig_size

int
bjoining_vis2cuni (unichar * vis, int len, unichar * ret, int *retlen,
		   int options)
{
  enum
  { NO, YES }
  join;
  int p, q, save = 0;
  con_shape_type **f =
    (con_shape_type **) malloc (len * sizeof (con_shape_type *));
  int *shape = (int *) malloc (len * sizeof (int));
  int type;
  int dir, startindex, endindex, counter, hasprev;
  int zwnl = 0;
  int *stoplig = 0;
  int nls;
  int nls_tab[5][3] = {
    {0, 0, 1},
    {2, 0, 1},
    {2, 3, 1},
    {4, 3, 1},
    {4, 3, 5},
  };
  unichar lig;

  if (0 == (options & B_LOGICAL_OUTPUT))
    {
      startindex = len - 1;
      endindex = 0;
      dir = -1;
    }
  else
    {
      startindex = 0;
      endindex = len - 1;
      dir = +1;
    }
  for (counter = len, p = startindex, join = NO; counter; --counter, p += dir)
    {
      f[p] = find_con_shape (vis[p]);
      type = f[p] ? f[p]->num : (bjoining_isnonspacing (vis[p]) ? 0 : 1);
      switch (type)
	{
	case 0:
	  shape[p] = ISOLATED;
	  break;
	case 1:
	  if (join == YES)
	    {
	      shape[save] = (shape[save] == MEDIAL) ? FINAL : ISOLATED;
	      join = NO;
	    }
	  shape[p] = ISOLATED;
	  break;
	case 2:
	  shape[p] = join ? FINAL : ISOLATED;
	  join = NO;
	  break;
	case 4:
	  shape[p] = join ? MEDIAL : INITIAL;
	  save = p;
	  join = YES;
	}
    }

  if (join == YES)
    shape[save] = (shape[save] == MEDIAL) ? FINAL : ISOLATED;

  if (0 == (options & B_NO_ZWJZWNJZWJ))
    {
      for (counter = len, zwnl = 0, nls = 0, p = endindex; counter;
	   --counter, p -= dir)
	{
	  switch (vis[p])
	    {
	    case ZWJ:
	      nls = nls_tab[nls][0];
	      break;
	    case ZWNJ:
	      nls = nls_tab[nls][1];
	      break;
	    default:
	      nls = nls_tab[nls][2];
	      break;
	    }
	  if (nls == 5)
	    {
	      if (zwnl == 0)
		{
		  stoplig = malloc (len * sizeof stoplig[0]);
		  memset (stoplig, 0, len * sizeof stoplig[0]);
		  zwnl = 1;
		}
	      stoplig[p] = 1;
	      nls = 1;
	    }
	}
    }

  for (counter = len, hasprev = 0, p = q = endindex; counter;
       --counter, p -= dir)
    {
      if (f[p] && f[p]->num)
	{
	  ret[q] = f[p]->shape[shape[p]];
	}
      else
	ret[q] = vis[p];
      if ((0 == (options & B_NO_LA_LIGATURE)) && hasprev
	  && ((0 != (options & B_NO_ZWJZWNJZWJ) || !zwnl || stoplig[p] == 0))
	  && (lig = arablig (ret[q], ret[q + dir])) != NOLIG)
	{
	  ret[q + dir] = lig;
	}
      else
	{
	  if (ret[q] != DELETE || 0 != (options & B_KEEP_JOINING_MARKS))
	    q -= dir;
	}
      hasprev = 1;
    }

  *retlen = endindex - q * dir;
  if (dir == 1)
    memmove (ret, ret + len - *retlen, *retlen * sizeof ret[0]);
  free (f);
  free (shape);
  if (zwnl)
    free (stoplig);
  return 1;
}
