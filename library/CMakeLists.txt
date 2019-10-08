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
        ${ROOT}/filter/gpu_image_vibrance_filter.hpp
        ${ROOT}/filter/gpu_image_two_input_filter.cpp
        ${ROOT}/filter/gpu_image_add_blend_filter.cpp
        ${ROOT}/filter/gpu_image_toon_filter.hpp
        ${ROOT}/filter/gpu_image_gamma_filter.hpp
        ${ROOT}/filter/gpu_image_false_color_filter.hpp
        ${ROOT}/filter/gpu_image_exposure_filter.hpp
        ${ROOT}/filter/gpu_image_exclusion_blend_filter.hpp
        ${ROOT}/filter/gpu_image_3x3_convolution_filter.hpp
        ${ROOT}/filter/gpu_image_emboss_filter.hpp
        ${ROOT}/filter/gpu_image_divide_blend_filter.hpp
        ${ROOT}/filter/gpu_image_mix_blend_filter.hpp
        ${ROOT}/filter/gpu_image_alpha_blend_filter.hpp
        ${ROOT}/filter/gpu_image_dissolve_blend_filter.hpp
        ${ROOT}/filter/gpu_image_directional_sobel_edge_detection_filter.hpp
        ${ROOT}/filter/gpu_image_grayscale_filter.hpp
        ${ROOT}/filter/gpu_image_sobel_edge_detection_filter.hpp
        ${ROOT}/filter/gpu_image_saturation_filter.hpp
        ${ROOT}/filter/gpu_image_contrast_filter.hpp
        ${ROOT}/filter/gpu_image_brightness_filter.hpp
        ${ROOT}/filter/gpu_image_levels_filter.hpp
        ${ROOT}/filter/gpu_image_rgb_filter.hpp
        ${ROOT}/filter/gpu_image_rgb_dilation_filter.hpp
        ${ROOT}/filter/gpu_image_hue_filter.hpp
        ${ROOT}/filter/gpu_image_monochrome_filter.hpp
        ${ROOT}/filter/gpu_image_sharpen_filter.hpp
        ${ROOT}/filter/gpu_image_highlight_shadow_filter.hpp
        ${ROOT}/filter/gpu_image_haze_filter.hpp
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



