#include "bconsole_ligature.h"

#include <stdlib.h>
#include <string.h>

#define NOLIG 0xFFFF

typedef struct
{
  unichar first, second, lig;
}
lig_type;

lig_type lig_tab[] = {
#include "bconsole_lig.i"
};

#define lig_size array_size(lig_tab)

unichar
ligature (unichar first, unichar second)
{
  int i;

  for (i = 0; i < lig_size; ++i)
    {
      if (first == lig_tab[i].first && second == lig_tab[i].second)
	{
	  return lig_tab[i].lig;
	}
    }
  return NOLIG;
}

typedef struct
{
  unichar code, without_tatweel, with_tatweel;
}
nsm_shape_type;

nsm_shape_type nsm_shape_tab[] = {
#include "bconsole_nsm_shape.i"
};

#define nsm_shape_size array_size(nsm_shape_tab)

nsm_shape_type *
nsm_shape (unichar code)
{
  int i;

  for (i = 0; i < nsm_shape_size; ++i)
    {
      if (code == nsm_shape_tab[i].code)
	{
	  return nsm_shape_tab + i;
	}
    }
  return NULL;
}

int
bconsole_ligature (unichar * us, int *retlen, int options)
{
  int p, q, len;
  unichar lig;
  enum
  { NO, YES }
  join;
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

  len = *retlen;
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
      if (bjoining_isnonspacing (us[p]))
	{
	  nsm_shape_type *t = nsm_shape (us[p]);
	  if (t)
	    us[p] = join ? t->with_tatweel : t->without_tatweel;
	}
      else
	join = join_type (us[p], 1);
    }

  if (0 == (options & B_NO_ZWJZWNJZWJ))
    {
      for (counter = len, zwnl = 0, nls = 0, p = endindex; counter;
	   --counter, p -= dir)
	{
	  switch (us[p])
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
		  stoplig = malloc (len * sizeof (stoplig[0]));
		  memset (stoplig, 0, len * sizeof (stoplig[0]));
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
      us[q] = us[p];
      if ((0 == (options & B_NO_EXTRA_LIGATURE)) && hasprev
	  && ((0 != (options & B_NO_ZWJZWNJZWJ) || !zwnl || stoplig[p] == 0))
	  && (lig = ligature (us[q], us[q + dir])) != NOLIG)
	{
	  us[q + dir] = lig;
	}
      else
	{
	  if ((us[q] != ZWJ && us[q] != ZWNJ)
	      || 0 != (options & B_KEEP_JOINING_MARKS))
	    q -= dir;
	}
      hasprev = 1;
    }
  *retlen = endindex - q * dir;
  if (dir == 1)
    memmove (us, us + len - *retlen, *retlen * sizeof us[0]);

  if (zwnl)
    free (stoplig);
  return 1;
}
