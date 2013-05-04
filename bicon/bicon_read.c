/*
 * Copyright (c) 2003 Muhammad Alkarouri.
 * Copyright (c) 2001,2002 Behdad Esfahbod.
 * All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <bconsole.h>

#define BUFLEN BUFSIZ
#define LATIN1 ((unsigned char)0xC0)
#define CSI ((unsigned char)(0x80+'\033'))
#define NONTERMINATED_PARAGRAPH -1

/* Console UTF-8 mode on/off sequences. */
#define UTF8_ON_STR "\033%G"
#define UTF8_OFF_STR "\033%@"

#define B_NO_UTF8_STARTUP   0x00010000	/* Do not start in UTF-8 mode. */
typedef unsigned char uchar;
int bicon_options = 0;
/*
LGPL code by Behdad Esfahbod
*/

unsigned char input[2][BUFLEN + 1], output[BUFLEN * 2];
unichar us[BUFLEN], cus[BUFLEN];
int turn, par_len, offset, del_num, utf8mode;
FriBidiCharSet utf8;


ssize_t
bicon_read (
  int fd,
  uchar *buf,
  size_t ct)
{
  int buflen;
  buflen = 0;

/*for (;;)*/
  {
    uchar *input_end, *output_cursor;
    int count;
    register uchar *input_cursor;

    /* Turn the turn ;-). */
    turn = 1 - turn;
    /* Read into input buffer. */
    count =
      read (fd, input[turn] + offset, sizeof (input[turn]) - 1 - offset);
    if (count == -1)
      return -1;
    count += offset;
    /* Null terminate string, for debug purposes only, no real need infact. */
    *(input_end = input[turn] + count) = '\0';

    /* Iterate over the input paragraph by paragraph. */
    input_cursor = input[turn];
    while (input_cursor < input_end)
      {
	int par_width = 0;
	uchar sigma_all;
	output_cursor = output;

	/* Find the next paragraph, the paragraph ends with any control
	 * character.  We can't do anything else about control characters. */
	{
	  register uchar y, x = 0, *par_cursor = input_cursor;
	  while (par_cursor < input_end
		 && ((y = *par_cursor) >= 0x20
		     && (y != LATIN1 || *(par_cursor + 1) >= 0xA0)))
	    {
	      x |= y;
	      par_cursor++;
	    }
	  par_len = par_cursor - input_cursor;
	  /* Sigma all is the bitwise OR of all characters in paragraph,
	   * we can check it's 8th bit to recognize that paragraph contains
	   * any non-ASCII character or not. */
	  sigma_all = x;
	}
	/* If an un-terminated paragraph in the previous round, and current
	 * text contains any non-ASCII character, we may need to rewrite
	 * the incomplete paragraph.  So add \b's to remove the old glyphs
	 * from the screen. */
	if (del_num > 0)
	  {
	    if (sigma_all & 0x80)
	      {

		memset (output_cursor, '\b', del_num);
		output_cursor += del_num;
	      }
	    else
	      {
		/* Otherwise, we just don't rewrite the prefix of the current
		 * paragraph which has already been wrote. */
		input_cursor += offset;
		par_len -= offset;
	      }
	    del_num = 0;
	  }
	offset = 0;
	/* Just process non-empty paragraph. */
	if (par_len)
	  {
	    /* Recognize non-terminated paragraph.  If so, take a backup
	     * for later usage.  We can't handle long paragraphs :-(. */
	    if (utf8mode && input_cursor + par_len >= input_end
		&& par_len < sizeof input[turn] - 1)
	      {
		/* Set offset too. */
		memmove (input[1 - turn], input_cursor, offset = par_len);
		/* We will set del_num to appropriate value later. */
		del_num = NONTERMINATED_PARAGRAPH;
	      }
	    /* Do we have arabic characters? */
	    if (utf8mode && (sigma_all & 0x80))
	      {
		int len;

		/* non-ASCII text, process as needed. */
		/* Convert to Unicode. */
		len =
		  fribidi_charset_to_unicode (utf8, (char *) input_cursor,
					      par_len, us);
		/* Convert to contextual form (glyphs). */
		bconsole_log2con (us, len, cus, &len, bicon_options);
		/* In this stage the number of characters is the same as
		 * paragraph's width. */
		par_width = len;
		/* Convert back to UTF-8. */
		len =
		  fribidi_unicode_to_charset (utf8, cus, len,
					      (char *) output_cursor);
		/* Update output_cursor. */
		output_cursor += len;
		/* Finally write the output. */
		memmove (buf + buflen, output, output_cursor - output);
		buflen += output_cursor - output;
	      }
	    else
	      {
		/* ASCII text, just write out. */
		/* In ASCII text the number of characters is the same of
		 * paragraph's width too. */
		par_width = par_len;
		/* In this case we don't write any \b's, so no need to write
		 * output buffer. */
		/* Write the input buffer out directly. */
		memmove (buf + buflen, input_cursor, par_len);
		buflen += par_len;
	      }
	    /* Move input_cursor forward. */
	    input_cursor += par_len;
	  }

	/* Now we should handle control characters, no process on them, so no
	 * output buffer needed, set output_cursor to point to input_cursor. */
	output_cursor = input_cursor;
	/* If non-terminated paragraph, save the par_width, to remove it
	 * in the next run. */
	if (del_num == NONTERMINATED_PARAGRAPH)
	  {
	    del_num = par_width;
	    /* If non-terminated paragraph, there's no other character,
	     * so continue. */
	    continue;
	  }
	{
	  register uchar x;

	  /* Go forward until there are control characters. */
	  while ((x = *input_cursor)
		 && (x < 0x20 || (x == LATIN1 && *(input_cursor + 1) < 0xA0)))
	    {
	      input_cursor++;
	      /* Skip over escape sequences */
	      if (x == '\033' || (x == LATIN1 && *input_cursor == CSI))
		{
		  /* Handle utf8 turn on/off sequences. */
		  utf8mode ^=
		    !strcmp (input_cursor - 1,
			     utf8mode ? UTF8_OFF_STR : UTF8_ON_STR);

		  /* An escape sequence looks like this: \033.[0-?]*[ -/]*[@-~]?
		   * We handle a somehow looser expression. */
		  input_cursor++;
		  while (*input_cursor >= '0' && *input_cursor <= '?')
		    input_cursor++;
		  while (*input_cursor >= ' ' && *input_cursor <= '/')
		    input_cursor++;
		  if (*input_cursor >= '@' && *input_cursor <= '~')
		    input_cursor++;
		}
	    }
	}
	/* Write out the control characters sequence. */
	memmove (buf + buflen, output_cursor, input_cursor - output_cursor);
	buflen += input_cursor - output_cursor;
      }
  }

  return buflen;
}

int
bicon_read_init (
  void)
{
  utf8 = fribidi_parse_charset ("UTF-8");
  if (!utf8)
    return 0;

  utf8mode = !(bicon_options & B_NO_UTF8_STARTUP);
  turn = offset = del_num = 0;

  return 1;
}
