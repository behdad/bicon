KEYMAPS = $(wildcard *.map)
KEYMAPSGZ = $(patsubst %.map,%.map.gz,$(KEYMAPS))

ARABICS = ae bh dz eg iq jo kw lb ly ma om qa sa sd sy tn ye
ARABICSMAPGZ = $(patsubst %,%.map.gz,$(ARABICS))

keymapdir = $(pkgdatadir)/keymap
dist_keymap_DATA = $(KEYMAPSGZ)

CLEANFILES = $(KEYMAPSGZ)

%.gz: %
	gzip -9 --stdout $< > $@

install-data-hook:
	cd "$(DESTDIR)/$(keymapdir)" && \
	for termapgz in $(ARABICSMAPGZ); do \
		if $(LN_S) arabic.map.gz $$termapgz; then \
			echo "Creating symlink for $$termapgz succeeded" ; \
		else \
			echo "Creating symlink for $$termapgz failed" ; \
		fi \
	done

uninstall-hook:
	cd "$(DESTDIR)/$(keymapdir)" && \
	$(RM) $(ARABICSMAPGZ)
