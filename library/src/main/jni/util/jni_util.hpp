//
// Created by ben622 on 2019/9/17.
//

#ifndef NATIVEGPUIMAGE_JNI_UTIL_HPP
#define NATIVEGPUIMAGE_JNI_UTIL_HPP

#include "../include/jni/JniHelpers.h"
#include "../gpu_image_render.hpp"
namespace ben{
    namespace jni{
        static ben::ngp::GPUImageRender* getNativeRenderInstance(JNIEnv *env, jobject javaThis){
            return registry.getNativeInstance<ben::ngp::GPUImageRender>(env, javaThis);
        }

    }
}

#endif //NATIVEGPUIMAGE_JNI_UTIL_HPP
