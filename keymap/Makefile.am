KEYMAPS = $(wildcard *.map)

keymapdir = $(pkgdatadir)/keymap
dist_keymap_DATA = $(patsubst %.map,%.map.gz,$(KEYMAPS))

%.gz: %
	@echo "Compressing $<"
	gzip -9 --stdout $< > $@

clean-local:
	$(RM) *.map.gz

install-data-hook:
	cd $(DESTDIR)$(keymapdir) && \
	$(LN_S) arabic.map.gz ae.map.gz && \
	$(LN_S) arabic.map.gz bh.map.gz && \
	$(LN_S) arabic.map.gz dz.map.gz && \
	$(LN_S) arabic.map.gz eg.map.gz && \
	$(LN_S) arabic.map.gz iq.map.gz && \
	$(LN_S) arabic.map.gz jo.map.gz && \
	$(LN_S) arabic.map.gz kw.map.gz && \
	$(LN_S) arabic.map.gz lb.map.gz && \
	$(LN_S) arabic.map.gz ly.map.gz && \
	$(LN_S) arabic.map.gz ma.map.gz && \
	$(LN_S) arabic.map.gz om.map.gz && \
	$(LN_S) arabic.map.gz qa.map.gz && \
	$(LN_S) arabic.map.gz sa.map.gz && \
	$(LN_S) arabic.map.gz sd.map.gz && \
	$(LN_S) arabic.map.gz sy.map.gz && \
	$(LN_S) arabic.map.gz tn.map.gz && \
	$(LN_S) arabic.map.gz ye.map.gz
uninstall-hook:
	cd $(DESTDIR)$(keymapdir) && \
	$(RM) ae.map.gz bh.map.gz dz.map.gz eg.map.gz iq.map.gz jo.map.gz \
	kw.map.gz lb.map.gz ly.map.gz ma.map.gz om.map.gz qa.map.gz \
	sa.map.gz sd.map.gz sy.map.gz tn.map.gz ye.map.gz || exit 0
