##############################################################################
## $Id$
## $Date$
## $Revision$
## $Source$
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

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
		`find -name Makefile.in` \
		`find "$(srcdir)" -name "*~"`

.PHONY: \
		indent \
		ChangeLog-maintain

indent: .indent.pro
	cd $(srcdir) && find -mindepth 2 -name "*.[ch]" | xargs indent

ChangeLog-maintain:
	cvs2cl
