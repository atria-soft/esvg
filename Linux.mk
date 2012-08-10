LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# name of the librairy
LOCAL_MODULE := parsersvg

# name of the dependency
LOCAL_STATIC_LIBRARIES := etk agg tinyxml

LOCAL_C_INCLUDES :=

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)

LOCAL_CFLAGS := -DPARSER_SVG_VERSION_TAG_NAME="\"???-$(BUILD_DIRECTORY_MODE)\""


# load the common sources file of the platform
include $(LOCAL_PATH)/file.mk

LOCAL_SRC_FILES := $(FILE_LIST)

include $(BUILD_STATIC_LIBRARY)
