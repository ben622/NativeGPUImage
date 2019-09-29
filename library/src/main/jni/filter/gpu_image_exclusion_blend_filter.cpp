//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_exclusion_blend_filter.hpp"

ben::ngp::GPUImageExclusionBlendFilter::GPUImageExclusionBlendFilter() : GPUImageTwoInputFilter(
        EXCLUSION_BLEND_FRAGMENT_SHADER) {

}

ben::ngp::GPUImageExclusionBlendFilter::GPUImageExclusionBlendFilter(JNIEnv *env)
        : GPUImageTwoInputFilter(EXCLUSION_BLEND_FRAGMENT_SHADER, env) {
    initialize(env);
}

const char *ben::ngp::GPUImageExclusionBlendFilter::getCanonicalName() const {
    return JAVA_EXCLUSION_BLEND_FILTER;
}
