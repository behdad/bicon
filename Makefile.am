##############################################################################
## $Id$
## $Author$
## $Date$
## $Revision$
## $Source$
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

## The order of subdirs is important, don't change without a reason.
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
		`find . -type f -name Makefile.in - print` \
		`find "$(srcdir)" -type f -name "*~" -print`

.PHONY: \
		indent \
		ChangeLog-maintain


# Indent all C source and header files

indent: .indent.pro
	find "$(srcdir)" -type f -mindepth 2 -name "*.[ch]" -print | xargs ./missing --run indent


# Creating ChangeLog from CVS log, with cvs2cl:

MAINTAINERCLEANFILES += ChangeLog

EXTRA_DIST = ChangeLog

ChangeLog:
	if test -d "$(srcdir)/CVS"; then \
		cd "$(srcdir)" && \
		./missing --run cvs2cl --stdout --utc --FSF -U AUTHORS; \
	fi > $@
