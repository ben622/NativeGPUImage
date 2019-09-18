//
// Created by ben622 on 2019/9/17.
//

#ifndef NATIVEGPUIMAGE_JNI_UTIL_HPP
#define NATIVEGPUIMAGE_JNI_UTIL_HPP

#include "../global_native_class_ptr.hpp"
#include "../gpu_image_render.hpp"

extern ben::jni::ClassRegistry *classRegistryPtr;
namespace ben{
    namespace jni{
        static const char *GPU_IMAGE_RENDER_CLASS = "com/ben/android/library/GPUImageRender";
        template<typename TypeName>
        static TypeName* getNativeClassPtr(const char* className){
            JavaClass *nativeClassPtr  = const_cast<JavaClass *>(classRegistryPtr->get(className));
            if (!nativeClassPtr) {
                LOGE("%s", "class not found!");
            }
            return dynamic_cast<TypeName *>(nativeClassPtr);
        }

    }
}

#endif //NATIVEGPUIMAGE_JNI_UTIL_HPP
