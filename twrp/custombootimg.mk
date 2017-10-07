TWRP_VERSION := $(shell cat $(call project-path-for,recovery)/variables.h | grep TW_MAIN_VERSION_STR | cut -d\" -s -f2)
TWRP_NAME := twrp-$(TWRP_VERSION)-$(TARGET_DEVICE)

LZMA_BIN := $(shell which lzma)

$(INSTALLED_RECOVERYIMAGE_TARGET): $(MKBOOTIMG) \
		$(recovery_ramdisk) \
		$(recovery_kernel)
	@echo ----- Compressing recovery ramdisk with lzma ------
	rm -f $(recovery_uncompressed_ramdisk).lzma
	$(LZMA_BIN) $(recovery_uncompressed_ramdisk)
	$(hide) cp $(recovery_uncompressed_ramdisk).lzma $(recovery_ramdisk)
	@echo ----- Making recovery image ------
	$(MKBOOTIMG) $(INTERNAL_RECOVERYIMAGE_ARGS) $(BOARD_MKBOOTIMG_ARGS) --output $@
	@echo ----- Made recovery image -------- $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_RECOVERYIMAGE_PARTITION_SIZE),raw)

	# Automatically make .tar flashable image
	@echo -e ${PRT_IMG}"----- Making odin recovery image ------"${CL_RST}
	cd $(PRODUCT_OUT) && tar -H ustar -c $(shell basename $@) > $(TWRP_NAME).tar
	cd $(PRODUCT_OUT) && md5sum -t $(TWRP_NAME).tar >> $(TWRP_NAME).tar
	mv $(PRODUCT_OUT)/$(TWRP_NAME).tar $(PRODUCT_OUT)/$(TWRP_NAME).tar.md5
	@echo -e ${PRT_IMG}"----- Made odin recovery image: $(PRODUCT_OUT)/$(TWRP_NAME).tar.md5 --------"${CL_RST}

$(INSTALLED_BOOTIMAGE_TARGET): $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_FILES)
	$(call pretty,"Target boot image: $@")
	$(hide) $(MKBOOTIMG) $(INTERNAL_BOOTIMAGE_ARGS) $(BOARD_MKBOOTIMG_ARGS) --output $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_BOOTIMAGE_PARTITION_SIZE),raw)
