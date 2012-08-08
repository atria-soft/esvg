LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# name of the librairy
LOCAL_MODULE := parsersvg

# name of the dependency
LOCAL_STATIC_LIBRARIES := etk agg tinyxml

LOCAL_C_INCLUDES :=

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

ifeq ($(DEBUG),1)
LOCAL_CFLAGS := -D__PLATFORM__Linux \
                -DSVG_DEBUG_LEVEL=3 \
                -DPARSER_SVG_VERSION_TAG_NAME="\"???-debug\""
else
LOCAL_CFLAGS := -D__PLATFORM__Linux \
                -DSVG_DEBUG_LEVEL=1 \
                -DPARSER_SVG_VERSION_TAG_NAME="\"???-release\""
endif

# load the common sources file of the platform
include $(LOCAL_PATH)/file.mk

LOCAL_SRC_FILES := $(FILE_LIST)

include $(BUILD_STATIC_LIBRARY)
