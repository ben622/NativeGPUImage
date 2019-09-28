//
// Created by ben622 on 2019/9/28.
//

#include "gpu_image_add_blend_filter.hpp"

ben::ngp::GPUImageAddBlendFilter::GPUImageAddBlendFilter()
        : GPUImageTwoInputFilter(ADD_BLEND_FRAGMENT_SHADER) {

}

ben::ngp::GPUImageAddBlendFilter::GPUImageAddBlendFilter(JNIEnv *env) : GPUImageTwoInputFilter(
        ADD_BLEND_FRAGMENT_SHADER, env) {
    initialize(env);
}

void ben::ngp::GPUImageAddBlendFilter::initialize(JNIEnv *env) {
    GPUImageTwoInputFilter::initialize(env);
}

void ben::ngp::GPUImageAddBlendFilter::mapFields() {
    GPUImageTwoInputFilter::mapFields();
}

const char *ben::ngp::GPUImageAddBlendFilter::getCanonicalName() const {
    return JAVA_ADD_BLEND_FILTER;
}
