AUTOMAKE_OPTIONS = gnu

SUBDIRS = bjoining bconsole bicon keymap font bin doc testtext

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = bicon.pc
                                                                                
MAINTAINERCLEANFILES = \
		ChangeLog.bak \
		INSTALL \
		aclocal.m4 \
		config.guess \
		config.h.in \
		config.sub \
		configure \
		depcomp \
		install-sh \
		ltmain.sh \
		missing \
		`find -name Makefile.in`

.PHONY: ChangeLog-update indent

ChangeLog-update:
	cvs2cl

indent:
	test -f .indent.pro || { echo ".indent.pro not found"; false; }
	find -name "*.[ch]" | xargs indent
