FONT=farsi-8x16.bdf.gz

all: farsi-8x16-512.psf.gz farsi-8x16-512-marks.psf.gz \
     farsi-8x16-512-logical.psf.gz farsi-8x16-512-marks-logical.psf.gz


%-set-names: %.bdf
	./bdf_set_names $< > $<~ && mv -f $<~ $< || { $(RM) $<~; false; }

%-set-names: %.bdf.gz
	./bdf_set_names $< | gzip -9 > $<~ && mv -f $<~ $< || \
	{ $(RM) $<~; false; }
	

farsi-8x16-512.psf.gz: $(FONT) farsi_arabic.sfm farsi_ascii.sfm farsi_nomarks.sfm
	./create_psf $@ $^

farsi-8x16-512-marks.psf.gz: $(FONT) farsi_arabic.sfm farsi_ascii.sfm farsi_marks.sfm
	./create_psf $@ $^

farsi-8x16-512-logical.psf.gz: $(FONT) farsi_arabic.sfm farsi_ascii.sfm farsi_nomarks.sfm
	./create_psf --mirrorrtl $@ $^

farsi-8x16-512-marks-logical.psf.gz: $(FONT) farsi_arabic.sfm farsi_ascii.sfm farsi_marks.sfm
	./create_psf --mirrorrtl $@ $^


clean:
	$(RM) *.psf.gz
