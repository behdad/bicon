INCLUDES = $(FRIBIDI_CFLAGS) -I../bjoining

noinst_LTLIBRARIES = libbconsole.la

libbconsole_la_SOURCES = bconsole_ligature.c bconsole_log2con.c \
                        bconsole_ligature.h bconsole_log2con.h bconsole.h \
			bconsole_lig.i bconsole_nsm_shape.i

noinst_PROGRAMS = bconsole_vu

bconsole_vu_SOURCES = bconsole_vu.c bconsole.h

bconsole_vu_LDADD = $(FRIBIDI_LIBS) libbconsole.la \
			$(top_builddir)/bjoining/libbjoining.la
