#include "bconsole_log2con.h"

#include <stdlib.h>

int
bconsole_log2con (
  unichar *str,
  int ulen,
  unichar *cstr,
  int *clen,
  int options)
{
  int f = 1;

  f = f
    && bjoining_log2cuni (str, ulen, cstr, clen,
			  options | B_KEEP_JOINING_MARKS);
  f = f && bconsole_ligature (cstr, clen, options);

  return f;
}
