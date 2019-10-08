//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_threshold_edge_detection_filter.hpp"
#include "gpu_image_sobel_threshold_filter.hpp"
#include "gpu_image_grayscale_filter.hpp"

ben::ngp::GPUImageThresholdEdgeDetectionFilter::GPUImageThresholdEdgeDetectionFilter():GPUImageFilterGroup() {}

ben::ngp::GPUImageThresholdEdgeDetectionFilter::GPUImageThresholdEdgeDetectionFilter(JNIEnv *env)
        : GPUImageFilterGroup(env) {
    initialize(env);
    addFilter(new GPUImageGrayscaleFilter());
    addFilter(new GPUImageSobelThresholdFilter());
}

void ben::ngp::GPUImageThresholdEdgeDetectionFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "size", kTypeFloat);
    cacheField(env, "threshold", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getThreshold", kTypeFloat, NULL);
    cacheMethod(env, "setThreshold", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getSize", kTypeFloat, NULL);
    cacheMethod(env, "setSize", kTypeVoid, kTypeFloat, NULL);
    merge(this);

}

void ben::ngp::GPUImageThresholdEdgeDetectionFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("size", kTypeFloat, &size);
    mapField("threshold", kTypeFloat, &threshold);
}

const char *ben::ngp::GPUImageThresholdEdgeDetectionFilter::getCanonicalName() const {
    return JAVA_THRESHOLD_EDGE_DETECTION_FILTER;
}

float ben::ngp::GPUImageThresholdEdgeDetectionFilter::getSize() const {
    return size;
}

void ben::ngp::GPUImageThresholdEdgeDetectionFilter::setSize(float size) {
    GPUImageThresholdEdgeDetectionFilter::size = size;
    GPUImage3x3TextureSamplingFilter *filter = dynamic_cast<GPUImage3x3TextureSamplingFilter *>(getFilters()[1]);
    filter->setLineSize(size);
}

float ben::ngp::GPUImageThresholdEdgeDetectionFilter::getThreshold() const {
    return threshold;
}

void ben::ngp::GPUImageThresholdEdgeDetectionFilter::setThreshold(float threshold) {
    GPUImageThresholdEdgeDetectionFilter::threshold = threshold;
    GPUImageSobelThresholdFilter *filter = dynamic_cast<GPUImageSobelThresholdFilter *>(getFilters()[1]);
    filter->setThreshold(size);
}
