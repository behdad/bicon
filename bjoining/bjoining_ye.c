#include "bjoining_ye.h"

/* should be applied on logical unicode string, not visual */
int
bjoining_ye_farsi_fix_for_ms (
  unichar * us,
  int len)
{
  int join;
  int p;

  for (p = len - 1, join = 0; p >= 0; --p)
    {
      if (!bjoining_isnonspacing (us[p]))
	{
	  if (join && us[p] == 0x06CC)
	    us[p] = 0x064A;
#ifdef REPLACE_ARABIC_YE
	  else if (!join && us[p] == 0x064A)
	    us[p] = 0x06CC;
#endif
	  join = join_type (us[p], 0);
	}
    }

  return 1;
}

/* should be applied on logical unicode string, not visual */
int
bjoining_ye_to_farsi (
  unichar * us,
  int len)
{
  int p;

  for (p = len - 1; p >= 0; --p)
    if (us[p] == 0x064A)
      us[p] = 0x06CC;

  return 1;
}
