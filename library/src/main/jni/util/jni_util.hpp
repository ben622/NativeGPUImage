//
// Created by ben622 on 2019/9/17.
//

#ifndef NATIVEGPUIMAGE_JNI_UTIL_HPP
#define NATIVEGPUIMAGE_JNI_UTIL_HPP

#include "../global_native_class_ptr.hpp"

extern ben::jni::ClassRegistry *classRegistryPtr;
namespace ben{
    namespace jni{
        static const char *GPU_IMAGE_RENDER_CLASS = "com/ben/android/library/NGPSurfaceView";

        template<typename TypeName>
        static TypeName* getNativeClassPtr(const char* className){
            JavaClass *nativeClassPtr  = const_cast<JavaClass *>(classRegistryPtr->get(className));
            if (!nativeClassPtr) {
                LOGE("Can't find class[%s], are you sure you registered in ClassRegister?", className);
                return NULL;
            }
            return dynamic_cast<TypeName *>(nativeClassPtr);
        }

        template<typename TypeName>
        static TypeName* getNativeInstancePtr(JNIEnv *env, jobject fromObject){
            return classRegistryPtr->getNativeInstance<TypeName>(env, fromObject);
        }

    }
}

#endif //NATIVEGPUIMAGE_JNI_UTIL_HPP
