#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bjoining.h"

#define BUFLEN 65000
#define UBUFLEN (BUFLEN * sizeof (unichar))

int
main (
  int argc,
  char **argv)
{
  int options;
  char s[BUFLEN];
  unichar us[BUFLEN], cus[BUFLEN];
  int len;
  FriBidiCharSet utf8;

  options = argc >= 2 ? atoi (argv[1]) : 0;
  utf8 = fribidi_parse_charset ("UTF-8");
  while (fgets (s, BUFLEN, stdin))
    {
      char *newline;
      len = strlen (s);
      if (s[len - 1] == '\n')
	{
	  newline = "\n";
	  s[--len] = '\0';
	}
      else
	newline = "";

      len = fribidi_charset_to_unicode (utf8, s, len, us);
      bjoining_log2cuni (us, len, cus, &len, options);
      len = fribidi_unicode_to_charset (utf8, cus, len, s);

      *(s + len) = '\0';
      printf ("%s%s", s, newline);
    }
  return 0;
}
