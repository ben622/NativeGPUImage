cmake_minimum_required(VERSION 3.4.1)
# support neon
ENABLE_LANGUAGE(ASM)

project("NativeGPUImageLibrary")

set(ROOT ${CMAKE_SOURCE_DIR}/src/main/jni)
set(PRELIB_ROOT ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
INCLUDE_DIRECTORIES(${ROOT}/include)


ADD_LIBRARY(gpuimage
        SHARED
        ${ROOT}/include/jni/JniHelpers.cpp
        ${ROOT}/include/jni/ByteArray.cpp
        ${ROOT}/include/jni/ClassRegistry.cpp
        ${ROOT}/include/jni/JavaClass.cpp
        ${ROOT}/include/jni/JavaClassUtils.cpp
        ${ROOT}/include/jni/JavaExceptionUtils.cpp
        ${ROOT}/include/jni/JavaString.cpp
        ${ROOT}/include/jni/JavaStringArray.cpp
        ${ROOT}/include/jni/JavaThreadUtils.cpp
        ${ROOT}/include/jni/NativeObject.cpp
        ${ROOT}/include/jni/ShortArray.cpp
        ${ROOT}/native_gpu_filter.cpp
        ${ROOT}/main.cpp)

#log
FIND_LIBRARY(log-lib
        log)


TARGET_LINK_LIBRARIES(gpuimage
        GLESv2
        EGL
        android
        ${log-lib})



