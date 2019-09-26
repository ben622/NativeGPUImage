//
// Created by ben622 on 2019/9/25.
// Android通过该接口进行gl交互
//

#ifndef NATIVEGPUIMAGE_ANDROID_GL_BRIDGE_HPP
#define NATIVEGPUIMAGE_ANDROID_GL_BRIDGE_HPP

#include "../include/jni/JniHelpers.h"
#include "android_native_filter.hpp"
#include "../filter/gpu_image_gaussian_blur_filter.hpp"
#include "../filter/gpu_image_pixelation_filter.hpp"
#include "../filter/gpu_image_dilation_filter.hpp"
#include "../filter/gpu_image_zoom_blur_filter.hpp"
#include "../filter/gpu_image_white_balance_filter.hpp"

using namespace ben::jni;
namespace ben{
    namespace ngp{
        class NGPNativeBridge:public JavaClass{
        public:
            NGPNativeBridge(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

        private:
            static void setFilter(JNIEnv *env, jclass javaThis, jobject object);
            static void setBitmap(JNIEnv *env, jclass javaThis, jobject object);
            static void requestRender(JNIEnv *env, jclass javaThis);
            static void capture(JNIEnv *env, jclass javaThis,jobject object);
        };
    }
}

#endif //NATIVEGPUIMAGE_ANDROID_GL_BRIDGE_HPP
