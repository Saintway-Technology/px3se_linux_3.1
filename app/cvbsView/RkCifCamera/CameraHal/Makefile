#CROSS_COMPILE ?= $(CURDIR)/../../../../toolschain/usr/bin/arm-linux-
#CROSS_COMPILE ?= /usr/bin/arm-linux-gnueabihf-
#CROSS_COMPILE ?=
include $(CURDIR)/productConfigs.mk
export CROSS_COMPILE
LOCAL_PATH:= $(CURDIR)
include $(LOCAL_PATH)/build_system/Makefile.rules
#include $(LOCAL_PATH)/productConfigs.mk

export  BUILD_OUPUT_EXTERNAL_LIBS
export  IS_ANDROID_OS
export  IS_NEED_SHARED_PTR
export  IS_NEED_COMPILE_STLPORT
export  IS_NEED_LINK_STLPORT
export  IS_NEED_COMPILE_TINYXML2
export  IS_NEED_COMPILE_EXPAT
export  IS_SUPPORT_ION
#export	IS_SUPPORT_DRM
export  IS_BUILD_TEST_APP
export	IS_CAM_IA10_API
export	IS_RK_ISP10
export  IS_USE_RK_V4L2_HEAD
export  IS_BUILD_TEST_APP

SUBDIRS ?=

ifeq ($(IS_NEED_COMPILE_STLPORT),true)
SUBDIRS += stlport
endif

ifeq ($(IS_NEED_COMPILE_TINYXML2),true)
SUBDIRS += tinyxml2
endif

ifeq ($(IS_NEED_COMPILE_EXPAT),true)
SUBDIRS += expat
endif
SUBDIRS += ebase oslayer cam_calibdb calib_xml cam_ia_api HAL

ifeq ($(IS_BUILD_TEST_APP),true)
SUBDIRS += testApp
SUBDIRS += test
SUBDIRS += dumpsys
endif

export BUILD_EVERYTHING
export CLEAN_EVERYTHING

define BUILD_EVERYTHING
	@+for subdir in $(SUBDIRS); \
	do \
	    echo "making $@ in $$subdir"; \
	    ( cd $$subdir && $(MAKE) -f Android.mk ) \
		|| exit 1; \
	done
endef

define CLEAN_EVERYTHING
	-rm -fr ./build
	-rm -f `find ./ -name *.o`
	-rm -f `find ./ -path "./libs" -prune -name *.a`
	-rm -f `find ./ -name *.so`
endef

.PHONY: all clean install

LIBS_FOR_LINK = $(addprefix ./build/lib/,$(notdir $(wildcard ./libs/*.a)))

all: ./build/lib/libcam_hal.so

./build/lib/libcam_hal.so: $(LIBS_FOR_LINK)
	$(BUILD_EVERYTHING)
	@echo $(@) done

clean:
	$(CLEAN_EVERYTHING)

install: ./build/lib/libcam_hal.so
	mkdir -p $(TARGET_DIR)/include/CameraHal
	cp -rf HAL/include/*		$(TARGET_DIR)/include/CameraHal/
	cp -rf include/CamHalVersion.h	$(TARGET_DIR)/include/CameraHal/
	cp -rf include/shared_ptr.h	$(TARGET_DIR)/include/
	cp -rf include/ebase		$(TARGET_DIR)/include/
	cp -rf include/oslayer		$(TARGET_DIR)/include/
	cp -rf include/linux		$(TARGET_DIR)/include/CameraHal/
	install ./build/lib/libcam_hal.so	$(TARGET_DIR)/lib
	@echo install libcam_hal.so!

./build/lib/%.a: ./libs/%.a
	cp $(<) $(@)
