keymapdir = $(pkgdatadir)/keymap
keymap_DATA = arab.kmap.gz isiri2901.kmap.gz

%.kmap.gz: %.kmap
	gzip --stdout $*.kmap > $@

clean-local:
	$(RM) *.kmap.gz
