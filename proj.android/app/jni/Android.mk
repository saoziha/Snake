LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp \
                   $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp \
                   $(LOCAL_PATH)/../../../Classes/Bullet.cpp \
                   $(LOCAL_PATH)/../../../Classes/CameraShake.cpp \
                   $(LOCAL_PATH)/../../../Classes/GameOverScene.cpp \
                   $(LOCAL_PATH)/../../../Classes/Heart.cpp \
                   $(LOCAL_PATH)/../../../Classes/Item.cpp \
                   $(LOCAL_PATH)/../../../Classes/MenuScreen.cpp \
                   $(LOCAL_PATH)/../../../Classes/Model.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneAbout.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneNewGame.cpp \
                   $(LOCAL_PATH)/../../../Classes/Rock.cpp \
                   $(LOCAL_PATH)/../../../Classes/SceneOption.cpp \
                   $(LOCAL_PATH)/../../../Classes/Snake.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-add-path, $(LOCAL_PATH)/../../../cocos2d)
$(call import-module, cocos)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
