//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_haze_filter.hpp"

ben::ngp::GPUImageHazeFilter::GPUImageHazeFilter():GPUImageFilter(NO_FILTER_VERTEX_SHADER, HAZE_FRAGMENT_SHADER) {}

ben::ngp::GPUImageHazeFilter::GPUImageHazeFilter(JNIEnv *env) : GPUImageFilter(NO_FILTER_VERTEX_SHADER, HAZE_FRAGMENT_SHADER,env) {
    initialize(env);
}

void ben::ngp::GPUImageHazeFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "distance", kTypeFloat);
    cacheField(env, "slope", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getDistance", kTypeFloat, NULL);
    cacheMethod(env, "setDistance", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getSlope", kTypeFloat, NULL);
    cacheMethod(env, "setSlope", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageHazeFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("distance", kTypeFloat, &distance);
    mapField("slope", kTypeFloat, &slope);
}

const char *ben::ngp::GPUImageHazeFilter::getCanonicalName() const {
    return JAVA_HAZE_FILTER;
}

void ben::ngp::GPUImageHazeFilter::onInit() {
    GPUImageFilter::onInit();
    distanceLocation = glGetUniformLocation(getGlProgId(), "distance");
    slopeLocation = glGetUniformLocation(getGlProgId(), "slope");
}

void ben::ngp::GPUImageHazeFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setDistance(distance);
    setSlope(slope);
}

void ben::ngp::GPUImageHazeFilter::setDistance(float distance) {
    GPUImageHazeFilter::distance = distance;
    setFloat(distanceLocation, distance);
}

void ben::ngp::GPUImageHazeFilter::setSlope(float slope) {
    GPUImageHazeFilter::slope = slope;
    setFloat(slopeLocation, slope);
}
