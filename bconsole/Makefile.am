INCLUDES = \
		$(FRIBIDI_CFLAGS) \
		-I$(top_srcdir)/bjoining

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

LDADD = \
		$(FRIBIDI_LIBS) \
		$(top_builddir)/bjoining/libbjoining.la \
		libbconsole.la
