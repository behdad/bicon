##############################################################################
## $Id$
## $Author$
## $Date$
## $Revision$
## $Source$
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

SUBDIRS = bjoining bconsole bicon keymap font bin doc testtext

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE@.pc

MAINTAINERCLEANFILES = \
		ChangeLog.bak \
		INSTALL \
		aclocal.m4 \
		autoscan.log \
		compile \
		config.guess \
		config.h.in \
		config.sub \
		configure \
		configure.scan \
		depcomp \
		install-sh \
		ltmain.sh \
		missing \
		`find -name Makefile.in` \
		`find "$(srcdir)" -name "*~"`

.PHONY: \
		indent \
		ChangeLog-maintain


# Indent all C source and header files

indent: .indent.pro
	@cd $(srcdir) && find -mindepth 2 -name "*.[ch]" | xargs ./missing --run indent


# Creating ChangeLog from CVS log, with cvs2cl:

MAINTAINERCLEANFILES += ChangeLog

EXTRA_DIST = ChangeLog

ChangeLog:
	@if test -d CVS; then \
		./missing --run cvs2cl --utc --FSF -U AUTHORS; \
	else \
		touch $@; \
	fi
