INCLUDES = $(FRIBIDI_CFLAGS)

noinst_LTLIBRARIES = libbjoining.la

libbjoining_la_SOURCES = bjoining_compose.c bjoining_charprop.c bjoining_vis2cuni.c bjoining_log2cuni.c bjoining_ye.c \
                        bjoining_compose.h bjoining_charprop.h bjoining_vis2cuni.h bjoining_log2cuni.h bjoining_ye.h \
                        arablig.i compose.i nonspace.i shape.i

noinst_PROGRAMS = bjoining_vu msye fixfarsiye

LDADD = $(FRIBIDI_LIBS) libbjoining.la
