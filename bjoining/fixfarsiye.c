#include <stdio.h>
#include <string.h>
#include "bjoining.h"

#define BUFLEN 65000
#define UBUFLEN (BUFLEN * sizeof (unichar))

int
main (
  )
{
  char s[BUFLEN];
  unichar us[BUFLEN];
  int len;
  FriBidiCharSet utf8;

  utf8 = fribidi_parse_charset ("UTF-8");
  while (fgets (s, BUFLEN, stdin))
    {
      char *newline;
      len = strlen (s);
      if (s[len - 1] == '\n')
	{
	  newline = "\n";
	  s[--len] = '\n';
	}
      else
	newline = "";

      len = fribidi_charset_to_unicode (utf8, s, len, us);
      bjoining_ye_to_farsi (us, len);
      len = fribidi_unicode_to_charset (utf8, us, len, s);

      *(s + len) = '\0';
      printf ("%s%s", s, newline);
    }
  return 0;
}
