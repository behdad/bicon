#include "bjoining_charprop.h"

struct
{
  unichar start, end;
}
nonspac_tab[] =
{
#include "nonspace.i"
};

#define ns_size array_size(nonspac_tab)
#define ns_start(i) nonspac_tab[i].start
#define ns_end(i) nonspac_tab[i].end

int
bjoining_isnonspacing (unichar u)
{
  int l, r, m;

  l = 0;
  r = ns_size - 1;
  while (l <= r)
    {
      m = (l + r) / 2;
      if (ns_start (m) > u)
	r = m - 1;
      else if (ns_end (m) < u)
	l = m + 1;
      else
	return 1;
    }
  return 0;
}
