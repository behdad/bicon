INCLUDES = \
		$(FRIBIDI_CFLAGS) \
		-I$(top_srcdir)/bjoining \
		-I$(top_srcdir)/bconsole

bin_PROGRAMS = bicon

bicon_SOURCES = \
		bicon.c \
		bicon_read.c \
		bicon_read.h \
		pty_spawn.c \
		pty_spawn.h

bicon_LDADD = \
		$(FRIBIDI_LIBS) \
		$(top_builddir)/bconsole/libbconsole.la \
		$(top_builddir)/bjoining/libbjoining.la

lib_LTLIBRARIES = libbicon.la

libbicon_la_SOURCES = bicon_so.c
libbicon_la_LIBADD = 
