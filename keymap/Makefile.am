keymapdir = $(pkgdatadir)/keymap
keymap_DATA = arab.kmap.gz isiri2901.kmap.gz

%.kmap.gz: %.kmap
	tar czvf $@ $*.kmap

clean-local:
	$(RM) *.kmap.gz
