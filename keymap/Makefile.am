KEYMAPS = $(wildcard *.map)

keymapdir = $(pkgdatadir)/keymap
keymap_DATA = $(patsubst %.map,%.map.gz,$(KEYMAPS))

%.gz: %
	gzip -9 --stdout $< > $@

clean-local:
	$(RM) *.map.gz
