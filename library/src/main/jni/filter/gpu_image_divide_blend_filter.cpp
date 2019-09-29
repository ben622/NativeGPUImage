//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_divide_blend_filter.hpp"

ben::ngp::GPUImageDivideBlendFilter::GPUImageDivideBlendFilter(JNIEnv *env)
        : GPUImageTwoInputFilter(DIVIDE_BLEND_FRAGMENT_SHADER, env) {
    initialize(env);
}

const char *ben::ngp::GPUImageDivideBlendFilter::getCanonicalName() const {
    return JAVA_DIVIDE_BLEND_FILTER;
}
