KEYMAPS = $(wildcard *.map)

keymapdir = $(pkgdatadir)/keymap
keymap_DATA = $(patsubst %.map,%.map.gz,$(KEYMAPS))

%.gz: %
	@echo "Compressing $<"
	gzip -9 --stdout $< > $@

clean-local:
	$(RM) *.map.gz

install-data-hook:
	cd $(keymapdir) && \
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
