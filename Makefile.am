AUTOMAKE_OPTIONS = gnu

EXTRA_DIST = \
		bootstrap \
		bicon.pc.in \
		keymap/arabic.map keymap/ir.map \
		doc/man/bicon.1 doc/man/bicon_console.1 \
		font/bdf_set_names font/bicon-8x16.bdf font/bicon-bdf2psf.pl \
		font/bicon-arabic.sfm font/bicon-ascii.sfm \
		font/bicon-marks.sfm font/bicon-nomarks.sfm \
		font/create_psf font/glyphlist.txt


SUBDIRS = bjoining bconsole bicon keymap font bin doc

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = bicon.pc
                                                                                
CLEANFILES = ChangeLog.bak
                                                                                
DISTCLEANFILES =
                                                                                
MAINTAINERCLEANFILES = Makefile.in aclocal.m4 config.h.in configure \
		INSTALL config.guess config.sub depcomp install-sh \
		ltmain.sh missing */Makefile.in
