cmake_minimum_required(VERSION 3.4.1)
# support neon
ENABLE_LANGUAGE(ASM)

project("NativeGPUImageLibrary")

set(ROOT ${CMAKE_SOURCE_DIR}/src/main/jni)
set(PRELIB_ROOT ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
INCLUDE_DIRECTORIES(${ROOT}/include)


add_subdirectory(${ROOT}/include/jni)
add_subdirectory(${ROOT}/libpng)

ADD_LIBRARY(gpuimage
        SHARED
        ${ROOT}/native_gpu_filter.cpp
        ${ROOT}/native_texture_image.cpp
        ${ROOT}/main.cpp)

#log
FIND_LIBRARY(log-lib
        log)


TARGET_LINK_LIBRARIES(gpuimage
        GLESv2
        EGL
        android
        libpng
        libjni
        ${log-lib})



