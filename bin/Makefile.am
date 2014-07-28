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
