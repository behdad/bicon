##############################################################################
## $Id$
## $Author$
## $Date$
## $Revision$
## $Source$
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

pkglib_LTLIBRARIES = libbjoining.la

libbjoining_la_SOURCES = \
		bjoining_compose.c \
		bjoining_charprop.c \
		bjoining_vis2cuni.c \
		bjoining_log2cuni.c \
		bjoining_ye.c
libbjoining_la_LIBADD = $(FRIBIDI_LIBS)

pkginclude_HEADERS = \
		bjoining_compose.h \
		bjoining_charprop.h \
		bjoining_vis2cuni.h \
		bjoining_log2cuni.h \
		bjoining_ye.h \
		bjoining.h

TABLE_FILES = \
                arablig.i \
		compose.i \
		nonspace.i \
		shape.i

EXTRA_DIST = \
		$(TABLE_FILES)

noinst_PROGRAMS = bjoining_vu msye fixpersianye

AM_CPPFLAGS = \
		$(FRIBIDI_CFLAGS)

LDADD = libbjoining.la $(FRIBIDI_LIBS)
