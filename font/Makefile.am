fontdir = $(pkgdatadir)/font
font_DATA = farsi-8x16-512.psf.gz farsi-8x16-512-marks.psf.gz \
     farsi-8x16-512-logical.psf.gz farsi-8x16-512-marks-logical.psf.gz

MFONT=farsi-8x16.bdf.gz

%-set-names: %.bdf
	./bdf_set_names $< > $<~ && mv -f $<~ $< || { $(RM) $<~; false; }

%-set-names: %.bdf.gz
	./bdf_set_names $< | gzip -9 > $<~ && mv -f $<~ $< || \
	{ $(RM) $<~; false; }
	

farsi-8x16-512.psf.gz: $(MFONT) farsi_arabic.sfm farsi_ascii.sfm farsi_nomarks.sfm
	./create_psf $@ $^

farsi-8x16-512-marks.psf.gz: $(MFONT) farsi_arabic.sfm farsi_ascii.sfm farsi_marks.sfm
	./create_psf $@ $^

farsi-8x16-512-logical.psf.gz: $(MFONT) farsi_arabic.sfm farsi_ascii.sfm farsi_nomarks.sfm
	./create_psf --mirrorrtl $@ $^

farsi-8x16-512-marks-logical.psf.gz: $(MFONT) farsi_arabic.sfm farsi_ascii.sfm farsi_marks.sfm
	./create_psf --mirrorrtl $@ $^


clean-local:
	$(RM) *.psf.gz
