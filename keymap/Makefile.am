KEYMAPS = $(wildcard *.map)

ARABICS = ae bh dz eg iq jo kw lb ly ma om qa sa sd sy tn ye

ARABICSMAPGZ = $(patsubst %,%.map.gz,$(ARABICS))

keymapdir = $(pkgdatadir)/keymap
dist_keymap_DATA = $(patsubst %.map,%.map.gz,$(KEYMAPS))

%.gz: %
	gzip -9 --stdout $< > $@

clean-local:
	$(RM) *.map.gz

install-data-hook:
	cd "$(DSTDIR)/$(keymapdir)" && \
	for termapgz in $(ARABICSMAPGZ); do \
		if $(LN_S) arabic.map.gz $$termapgz; then \
			echo "Creating symlink for $$ter.map.gz succeeded" ; \
		else \
			echo "Creating symlink for $$ter.map.gz failed" ; \
		fi \
	done

uninstall-hook:
	cd "$(DSTDIR)/$(keymapdir)" && \
	$(RM) $(ARABICSMAPGZ)
