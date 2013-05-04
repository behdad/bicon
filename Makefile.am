##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in
##############################################################################
## $Id$
## $Author$
## $Date$
## $Revision$
## $Source$
##############################################################################

## The order of subdirs is important, don't change without a reason.
SUBDIRS = bjoining bconsole bicon keymap font bin doc testtext

EXTRA_DIST = autogen.sh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = @PACKAGE@.pc

MAINTAINERCLEANFILES = \
	$(GITIGNORE_MAINTAINERCLEANFILES_TOPLEVEL) \
	$(GITIGNORE_MAINTAINERCLEANFILES_M4_LIBTOOL) \
	$(GITIGNORE_MAINTAINERCLEANFILES_MAKEFILE_IN) \
	$(srcdir)/INSTALL \
	$(srcdir)/ChangeLog \
	$(NULL)

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

-include $(top_srcdir)/git.mk
