AUTOMAKE_OPTIONS = gnu

SUBDIRS = bjoining bconsole bicon keymap font bin doc testtext

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = bicon.pc
                                                                                
MAINTAINERCLEANFILES = \
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

MOSTLYCLEANFILES = ChangeLog.bak

if MAINTAINER_MODE

.PHONY: ChangeLog-update indent

ChangeLog-update:
	cvs2cl

indent: .indent.pro
	cd $(srcdir) && find -mindepth 2 -name "*.[ch]" | xargs indent

MOSTLYCLEANFILES += `find "$(srcdir)" -name "*~"`

endif
