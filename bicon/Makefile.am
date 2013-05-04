##############################################################################
## $Id: Makefile.am,v 1.8 2004/04/13 08:42:08 behdad Exp $
## $Author: behdad $
## $Date: 2004/04/13 08:42:08 $
## $Revision: 1.8 $
## $Source: /home/arabeyes/cvs/projects/bicon/bicon/Makefile.am,v $
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

bin_PROGRAMS = bicon.bin

bicon_bin_SOURCES = \
		bicon.c \
		bicon_read.c \
		bicon_read.h \
		pty_spawn.c \
		pty_spawn.h

bicon_bin_CPPFLAGS = \
		$(FRIBIDI_CFLAGS) \
		-I$(top_srcdir)/bjoining \
		-I$(top_srcdir)/bconsole

bicon_bin_LDADD = \
		$(FRIBIDI_LIBS) \
		$(top_builddir)/bconsole/libbconsole.la \
		$(top_builddir)/bjoining/libbjoining.la

#lib_LTLIBRARIES = libbicon.la
#
#libbicon_la_SOURCES = bicon_so.c
#libbicon_la_LIBADD = 
