#include "bjoining_compose.h"

#include <string.h>

struct
{
  unichar first, second, comp;
}
arab_comp[] =
{
#include "compose.i"
};

#define comp_size array_size(arab_comp)

int
bjoining_compose (unichar * u, int *unilen)
{
  int p, i;

  for (p = 0; p < *unilen - 1; ++p)
    {
      for (i = 0; i < comp_size; ++i)
	{
	  if (u[p] == arab_comp[i].first && u[p + 1] == arab_comp[i].second)
	    {
	      u[p] = arab_comp[i].comp;
	      memmove (u + p + 1, u + p + 2,
		       ((*unilen) - p - 2) * sizeof (unichar));
	      --(*unilen);
	    }
	}
    }
  return 1;
}
