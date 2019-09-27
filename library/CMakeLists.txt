cmake_minimum_required(VERSION 3.4.1)
# support neon
ENABLE_LANGUAGE(ASM)

project("NativeGPUImageLibrary")

set(ROOT ${CMAKE_SOURCE_DIR}/src/main/jni)
set(PRELIB_ROOT ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${ANDROID_ABI})
INCLUDE_DIRECTORIES(${ROOT}/include)


add_subdirectory(${ROOT}/include/jni)
add_subdirectory(${ROOT}/include/lib_json)
add_subdirectory(${ROOT}/filter)
add_subdirectory(${ROOT}/api)

ADD_LIBRARY(gpuimage
        SHARED
        ${ROOT}/include/queue.c
        ${ROOT}/filter/gpu_image_dilation_filter.cpp
        ${ROOT}/filter/gpu_image_zoom_blur_filter.hpp
        ${ROOT}/filter/gpu_image_white_balance_filter.cpp
        ${ROOT}/filter/gpu_image_3x3_texture_sampling_filter.hpp
        ${ROOT}/filter/gpu_image_weak_pixel_inclusion_filter.hpp
        ${ROOT}/filter/gpu_image_vignette_filter.hpp
        ${ROOT}/global_native_class_ptr.cpp
        ${ROOT}/gpu_image_render.cpp
        ${ROOT}/main.cpp)

#log
FIND_LIBRARY(log-lib
        log)


TARGET_LINK_LIBRARIES(gpuimage
        GLESv2
        EGL
        jnigraphics
        android
        libjni
        libfilter
        libapi
        ${log-lib})



