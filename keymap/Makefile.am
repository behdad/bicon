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
	$(LN_S) ar.map.gz ae.map.gz && \
	$(LN_S) ar.map.gz bh.map.gz && \
	$(LN_S) ar.map.gz dz.map.gz && \
	$(LN_S) ar.map.gz eg.map.gz && \
	$(LN_S) ar.map.gz iq.map.gz && \
	$(LN_S) ar.map.gz jo.map.gz && \
	$(LN_S) ar.map.gz kw.map.gz && \
	$(LN_S) ar.map.gz lb.map.gz && \
	$(LN_S) ar.map.gz ly.map.gz && \
	$(LN_S) ar.map.gz ma.map.gz && \
	$(LN_S) ar.map.gz om.map.gz && \
	$(LN_S) ar.map.gz qa.map.gz && \
	$(LN_S) ar.map.gz sa.map.gz && \
	$(LN_S) ar.map.gz sd.map.gz && \
	$(LN_S) ar.map.gz sy.map.gz && \
	$(LN_S) ar.map.gz tn.map.gz && \
	$(LN_S) ar.map.gz ye.map.gz
