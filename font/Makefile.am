fontdir = $(pkgdatadir)/font
font_DATA = \
		bicon-8x16-512.psfu.gz \
		bicon-8x16-512-marks.psfu.gz \
		bicon-8x16-512-logical.psfu.gz \
		bicon-8x16-512-marks-logical.psfu.gz

SUBSFMS = \
		bicon-ascii.sub-sfm \
		bicon-arabic.sub-sfm \
		bicon-nomarks.sub-sfm \
		bicon-marks.sub-sfm
TOOLS = \
		bicon-bdf2psf.pl

EXTRA_DIST = $(BDF) $(SUBSFMS) $(TOOLS)

BDF2PSF = "$(srcdir)/bicon-bdf2psf.pl"



# font to use
BDF = bicon-8x16.bdf

all: $(font_DATA)

clean-local:
	$(RM) *.sfm *.psf *.psfu *.psfu.gz

%-set-names: %.bdf
	"$(srcdir)/bdf_set_names" $< > $<~ && mv -f $<~ $< || { $(RM) $<~; false; }

%-logical.psf: %.sfm $(BDF)
	$(BDF2PSF) -m -s $< -o $@ < "$(srcdir)/$(BDF)"

%.psf: %.sfm $(BDF)
	$(BDF2PSF) -s $< -o $@ < "$(srcdir)/$(BDF)"

%.psfu: %.psf %.sfm
	psfaddtable $^ $@

%.gz: %
	gzip -9 --stdout $< > $@

bicon-8x16-512.sfm: bicon-ascii.sub-sfm bicon-arabic.sub-sfm bicon-nomarks.sub-sfm
	cat $^ > $@

bicon-8x16-512-marks.sfm: bicon-ascii.sub-sfm bicon-arabic.sub-sfm bicon-marks.sub-sfm
	cat $^ > $@

bicon-8x16-512-logical.sfm: bicon-ascii.sub-sfm bicon-arabic.sub-sfm bicon-nomarks.sub-sfm
	cat $^ > $@

bicon-8x16-512-marks-logical.sfm: bicon-ascii.sub-sfm bicon-arabic.sub-sfm bicon-marks.sub-sfm
	cat $^ > $@
