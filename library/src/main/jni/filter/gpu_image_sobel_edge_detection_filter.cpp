//
// Created by ben622 on 2019/9/29.
//

#include "gpu_image_sobel_edge_detection_filter.hpp"

ben::ngp::GPUImageSobelEdgeDetectionFilter::GPUImageSobelEdgeDetectionFilter(JNIEnv *env):GPUImageFilterGroup(env){
    initialize(env);
    addFilter(new GPUImageGrayscaleFilter());
    addFilter(new GPUImage3x3TextureSamplingFilter(SOBEL_EDGE_DETECTION_SOURCE));
}

const char *ben::ngp::GPUImageSobelEdgeDetectionFilter::getCanonicalName() const {
    return JAVA_SOBEL_EDGE_DETECTION_FILTER;
}

void ben::ngp::GPUImageSobelEdgeDetectionFilter::setSize(float size) {
    GPUImageSobelEdgeDetectionFilter::size = size;
    GPUImage3x3TextureSamplingFilter *filter = dynamic_cast<GPUImage3x3TextureSamplingFilter *>(getFilters()[1]);
    filter->setLineSize(size);
}

void ben::ngp::GPUImageSobelEdgeDetectionFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "size", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getSize", kTypeFloat, NULL);
    cacheMethod(env, "setSize", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageSobelEdgeDetectionFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("size", kTypeFloat, &size);
}

float ben::ngp::GPUImageSobelEdgeDetectionFilter::getSize() const {
    return size;
}

