ALL_CONSOLE_FONTS = \
		bicon-8x16-512 \
		bicon-8x16-512-marks \
		bicon-8x16-512-ltr \
		bicon-8x16-512-marks-ltr

ALL_CONSOLE_FONTS_SFM = $(ALL_CONSOLE_FONTS:=.sfm)
ALL_CONSOLE_FONTS_PSFU = $(ALL_CONSOLE_FONTS:=.psfu)

ALL_SUBSFMS = \
		bicon-ascii.sub-sfm \
		bicon-arabic.sub-sfm \
		bicon-nomarks.sub-sfm \
		bicon-marks.sub-sfm

# font to use
BDF = bicon-8x16.bdf
