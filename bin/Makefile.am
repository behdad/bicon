bin_SCRIPTS=bicon

edit = sed \
	-e 's,@datadir\@,$(pkgdatadir),g' \
	-e 's,@bindir\@,$(bindir),g' \
	-e 's,@prefix\@,$(prefix),g'
                                                                               
bicon: $(srcdir)/bicon.in Makefile
	rm -f $@ $@.tmp
	$(edit) $< > $@.tmp
	chmod +x $@.tmp
	mv $@.tmp $@

MOSTLYCLEANFILES=bicon.tmp
CLEANFILES=bicon
