##############################################################################
## $Id$
## $Author$
## $Date$
## $Revision$
## $Source$
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

include fonts.mk

ALL_CONSOLE_FONTS_PSFU_GZ = $(ALL_CONSOLE_FONTS_PSFU:=.gz)

fontdir = $(pkgdatadir)/font
dist_font_DATA = $(ALL_CONSOLE_FONTS_PSFU_GZ) $(BDF)
noinst_DATA = $(ALL_CONSOLE_FONTS_SFM)

EXTRA_DIST = $(ALL_SUBSFMS) bicon-bdf2psf.pl

BDF2PSF = $(srcdir)/bicon-bdf2psf.pl

CLEANFILES = *.sfm *.psf *.psfu *.psfu.gz *.tmp

SUFFIXES = .bdf .bdf-maintain .sfm -ltr.sfm .psf -ltr.psf .psfu .psfu.gz

# Note:  I replaced the non-portable rules below with old suffix way to make
# them portable.  But unfortunately this way the dependancies like %.psf: $(BDF)
# do not work anymore :(.  Perhaps a check for GNU make should happen...

# %.psfu.gz: %.psfu
.psfu.psfu.gz:
	gzip --best -c $< > $@

# %-set-names: %.bdf
.bdf.bdf-maintain:
	$(srcdir)/bdf_set_names $< > $<.tmp && mv -f $<.tmp $<

# %-ltr.psf: %.sfm $(BDF) $(BDF2PSF)
.sfm-ltr.psf: $(BDF) $(BDF2PSF)
	$(BDF2PSF) -m -s $< -o $@ < $(srcdir)/$(BDF)

# %.psf: %.sfm $(BDF) $(BDF2PSF)
.sfm.psf: $(BDF) $(BDF2PSF)
	$(BDF2PSF) -s $< -o $@ < $(srcdir)/$(BDF)

# %-ltr.sfm: %.sfm
.sfm-ltr.sfm:
	$(LN_S) $< $@

# %.psfu: %.psf %.sfm
.psf.psfu:
	$(MAKE) $(AM_MAKEFLAGS) $*.sfm
	psfaddtable $*.psf $*.sfm $*.psfu

bicon-8x16-512.sfm: bicon-ascii.sub-sfm bicon-arabic.sub-sfm bicon-nomarks.sub-sfm
	cat $^ > $@

bicon-8x16-512-marks.sfm: bicon-ascii.sub-sfm bicon-arabic.sub-sfm bicon-marks.sub-sfm
	cat $^ > $@

-include $(top_srcdir)/git.mk
