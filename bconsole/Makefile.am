INCLUDES = $(FRIBIDI_CFLAGS) -I../bjoining

lib_LTLIBRARIES = libbconsole.la

libbconsole_la_SOURCES = \
		bconsole_ligature.c \
		bconsole_log2con.c

libbconsoleincdir = $(includedir)/bicon/bconsole

libbconsoleinc_HEADERS = \
		bconsole_ligature.h \
		bconsole_log2con.h \
		bconsole.h

TABLE_FILES = \
		bconsole_lig.i \
		bconsole_nsm_shape.i

EXTRA_DIST = \
		$(TABLE_FILES)

noinst_PROGRAMS = bconsole_vu

bconsole_vu_SOURCES = bconsole_vu.c bconsole.h

bconsole_vu_LDADD = $(FRIBIDI_LIBS) libbconsole.la \
		$(top_builddir)/bjoining/libbjoining.la
