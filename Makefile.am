##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in
##############################################################################
## $Id: Makefile.am,v 1.25 2004/08/27 21:54:19 behdad Exp $
## $Author: behdad $
## $Date: 2004/08/27 21:54:19 $
## $Revision: 1.25 $
## $Source: /home/arabeyes/cvs/projects/bicon/Makefile.am,v $
##############################################################################

## The order of subdirs is important, don't change without a reason.
SUBDIRS = bjoining bconsole bicon keymap font bin doc testtext

EXTRA_DIST = autogen.sh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE@.pc

MAINTAINERCLEANFILES = \
		$(srcdir)/INSTALL \
		$(srcdir)/aclocal.m4 \
		$(srcdir)/autoscan.log \
		$(srcdir)/compile \
		$(srcdir)/config.guess \
		$(srcdir)/config.h.in \
		$(srcdir)/config.sub \
		$(srcdir)/configure \
		$(srcdir)/configure.scan \
		$(srcdir)/depcomp \
		$(srcdir)/install-sh \
		$(srcdir)/ltmain.sh \
		$(srcdir)/missing \
		`find "$(srcdir)" -type f -name Makefile.in -print` \
		`find "$(srcdir)" -type f -name "*~" -print`

# Indent all C source and header files, using indent(1):

indent: $(srcdir)/.indent.pro
	cd "$(srcdir)" && \
	find . -mindepth 2 -type f -name "*.[ch]" -print | \
	  xargs ./missing --run indent

.PHONY: indent


MAINTAINERCLEANFILES += ChangeLog


#
# ChangeLog generation
#
CHANGELOG_RANGE =
ChangeLog:
	$(AM_V_GEN) if test -d "$(top_srcdir)/.git"; then \
	  (GIT_DIR=$(top_srcdir)/.git $(top_srcdir)/missing --run \
	   git log $(CHANGELOG_RANGE) --stat) | fmt --split-only > $@.tmp \
	  && mv -f $@.tmp "$(srcdir)/ChangeLog" \
	  || ($(RM) $@.tmp; \
	      echo Failed to generate ChangeLog, your ChangeLog may be outdated >&2; \
	      (test -f $@ || echo git-log is required to generate this file >> "$(srcdir)/$@")); \
	else \
	  test -f $@ || \
	  (echo A git checkout and git-log is required to generate ChangeLog >&2 && \
	  echo A git checkout and git-log is required to generate this file >> "$(srcdir)/$@"); \
	fi
.PHONY: $(srcdir)/ChangeLog
