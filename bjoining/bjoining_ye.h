#ifndef __BJOINING_YE_H
#define __BJOINING_YE_H

#include "bjoining.h"

#define REPLACE_ARABIC_YE

/* should be applied on logical unicode string, not visual */
int bjoining_ye_farsi_fix_for_ms (
  unichar *us,
  int len);

/* should be applied on logical unicode string, not visual */
int bjoining_ye_to_farsi (
  unichar *us,
  int len);

#endif
