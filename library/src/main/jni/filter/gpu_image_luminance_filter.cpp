//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_luminance_filter.hpp"

ben::ngp::GPUImageLuminanceFilter::GPUImageLuminanceFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, LUMINANCE_FRAGMENT_SHADER,env) {
    initialize(env);
}

const char *ben::ngp::GPUImageLuminanceFilter::getCanonicalName() const {
    return JAVA_LUMINANCE_FILTER;
}
