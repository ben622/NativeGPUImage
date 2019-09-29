//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_directional_sobel_edge_detection_filter.hpp"

ben::ngp::GPUImageDirectionalSobelEdgeDetectionFilter::GPUImageDirectionalSobelEdgeDetectionFilter(
        JNIEnv *env) : GPUImage3x3TextureSamplingFilter(env,DIRECTIONAL_SOBEL_EDGE_DETECTION_FRAGMENT_SHADER) {
    initialize(env);
}

void ben::ngp::GPUImageDirectionalSobelEdgeDetectionFilter::initialize(JNIEnv *env) {
    GPUImage3x3TextureSamplingFilter::initialize(env);
}

void ben::ngp::GPUImageDirectionalSobelEdgeDetectionFilter::mapFields() {
    GPUImage3x3TextureSamplingFilter::mapFields();
}

const char *ben::ngp::GPUImageDirectionalSobelEdgeDetectionFilter::getCanonicalName() const {
    return JAVA_DIRECTIONAL_SOBEL_EDGE_DETECTION_FILTER;
}
