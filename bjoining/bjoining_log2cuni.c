#include "bjoining_log2cuni.h"

#include <stdlib.h>
#include <string.h>

int
bjoining_log2cuni (
  unichar *str,
  int ulen,
  unichar *cstr,
  int *clen,
  int options)
{
  int f = 1;
  int len = ulen;
  FriBidiCharType ptype = FRIBIDI_TYPE_ON;

  unichar *vis = malloc ((len + 1) * sizeof (unichar));

  f = f && bjoining_compose (str, &len);
  if (0 == (options & B_LOGICAL_OUTPUT))
    {
      f = f
	&& fribidi_log2vis ((FriBidiChar *) str, len, &ptype,
			    (FriBidiChar *) vis, NULL, NULL, NULL);
    }
  else
    {
      memmove (vis, str, len * sizeof str[0]);
    }
  if (0 == (options & B_KEEP_BIDI_MARKS))
    len = fribidi_remove_bidi_marks (vis, len, NULL, NULL, NULL);
  f = f && bjoining_vis2cuni (vis, len, cstr, clen, options);
  if (f)
    cstr[*clen] = '\0';
  else
    clen = 0;
  free (vis);

  return f;
}
