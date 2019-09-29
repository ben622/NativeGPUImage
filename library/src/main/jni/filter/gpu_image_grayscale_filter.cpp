//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_grayscale_filter.hpp"

ben::ngp::GPUImageGrayscaleFilter::GPUImageGrayscaleFilter() : GPUImageFilter(NO_FILTER_VERTEX_SHADER, GRAYSCALE_FRAGMENT_SHADER){}
ben::ngp::GPUImageGrayscaleFilter::GPUImageGrayscaleFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, GRAYSCALE_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageGrayscaleFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
}

void ben::ngp::GPUImageGrayscaleFilter::mapFields() {
    GPUImageFilter::mapFields();
}

const char *ben::ngp::GPUImageGrayscaleFilter::getCanonicalName() const {
    return JAVA_GRAYSCALE_FILTER;
}


