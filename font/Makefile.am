fontdir = $(pkgdatadir)/font
font_DATA = bicon-8x16-512.psf.gz bicon-8x16-512-marks.psf.gz \
     bicon-8x16-512-logical.psf.gz bicon-8x16-512-marks-logical.psf.gz

all: $(font_DATA)
BDF=bicon-8x16.bdf

%-set-names: %.bdf
	$(srcdir)/bdf_set_names $< > $<~ && mv -f $<~ $< || { $(RM) $<~; false; }

bicon-8x16-512.psf: $(BDF) bicon-arabic.sfm bicon-ascii.sfm bicon-nomarks.sfm
	$(srcdir)/create_psf $@ $^

bicon-8x16-512-marks.psf: $(BDF) bicon-arabic.sfm bicon-ascii.sfm bicon-marks.sfm
	$(srcdir)/create_psf $@ $^

bicon-8x16-512-logical.psf: $(BDF) bicon-arabic.sfm bicon-ascii.sfm bicon-nomarks.sfm
	$(srcdir)/create_psf --mirrorrtl $@ $^

bicon-8x16-512-marks-logical.psf: $(BDF) bicon-arabic.sfm bicon-ascii.sfm bicon-marks.sfm
	$(srcdir)/create_psf --mirrorrtl $@ $^

%.gz: %
	@echo "Compressing $<"
	gzip -9 --stdout $< > $@

clean-local:
	$(RM) *.psf *.psf.gz
