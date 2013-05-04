##############################################################################
## $Id: Makefile.am,v 1.9 2004/04/13 08:42:08 behdad Exp $
## $Author: behdad $
## $Date: 2004/04/13 08:42:08 $
## $Revision: 1.9 $
## $Source: /home/arabeyes/cvs/projects/bicon/bin/Makefile.am,v $
##############################################################################
##                                               -*- Automake -*-
## Process this file with automake to produce Makefile.in

bin_SCRIPTS=bicon

do_subst = sed \
		-e 's,@datadir\@,$(pkgdatadir),g' \
		-e 's,@bindir\@,$(bindir),g' \
		-e 's,@PACKAGE_NAME\@,$(PACKAGE_NAME),g' \
		-e 's,@PACKAGE\@,$(PACKAGE),g' \
		-e 's,@VERSION\@,$(VERSION),g'
                                                                               
bicon: bicon.in Makefile
	$(do_subst) $(srcdir)/bicon.in > $@
	chmod +x $@

EXTRA_DIST = bicon.in

MOSTLYCLEANFILES=bicon.tmp
CLEANFILES=bicon

-include $(top_srcdir)/git.mk
