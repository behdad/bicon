#ifndef __BJOINING_H
#define __BJOINING_H

#define CONST const

#include <fribidi/fribidi.h>

typedef FriBidiChar unichar;

#define ZWNJ UNI_ZWNJ
#define ZWJ UNI_ZWJ


/* Options: */

/* Options that bjoining functions handle. */
#define B_KEEP_BIDI_MARKS	0x00000001	/* Do not remove bidi marks (LRM, RLM, ...). */
#define B_LOGICAL_OUTPUT	0x00000002	/* Do not perform bidi, just joining stuff. */
#define B_KEEP_JOINING_MARKS	0x00000010	/* Do not remove joining marks (ZWJ, ZWNJ). */
#define B_NO_LA_LIGATURE	0x00000020	/* Do not make LAM-ALEF ligature. */
#define B_NO_ZWJZWNJZWJ		0x00000040	/* Do not interpret ZWJ+ZWNJ+ZWJ sequences. */

/* Options that bconsole functions handle. */
#define B_NO_EXTRA_LIGATURE	0x00000100	/* Do not make other ligatures. */

/* Options that fcon handles. */
#define B_NO_UTF8_STARTUP	0x00010000	/* Do not start in UTF-8 mode. */


/* Options that cause some of above. */
#define B_KEEP_MARKS		(B_KEEP_BIDI_MARKS + B_KEEP_JOINING_MARKS)
#define B_NO_LIGATURE		(B_NO_LA_LIGATURE + B_NO_EXTRA_LIGATURE)


#include "bjoining_compose.h"
#include "bjoining_charprop.h"
#include "bjoining_vis2cuni.h"
#include "bjoining_log2cuni.h"
#include "bjoining_ye.h"

#define array_size(x) (sizeof (x) / sizeof (x[0]))

#endif
