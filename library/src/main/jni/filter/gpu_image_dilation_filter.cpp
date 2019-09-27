//
// Created by ben622 on 2019/9/20.
//

#include "gpu_image_dilation_filter.hpp"

ben::ngp::GPUImageDilationFilter::GPUImageDilationFilter(JNIEnv *env)
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER_2, FRAGMENT_SHADER_2, VERTEX_SHADER_2,
                                               FRAGMENT_SHADER_2, env) {
    //必须在构造函数执行完以后才可以进行JNI操作
    initialize(env);

}

ben::ngp::GPUImageDilationFilter::GPUImageDilationFilter()
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER_2, FRAGMENT_SHADER_2, VERTEX_SHADER_2,
                                               FRAGMENT_SHADER_2) {

}

ben::ngp::GPUImageDilationFilter::GPUImageDilationFilter(int radius)
        : GPUImageTwoPassTextureSamplingFilter(VERTEX_SHADER_2, FRAGMENT_SHADER_2, VERTEX_SHADER_2,
                                               FRAGMENT_SHADER_2) {

}

 const char *ben::ngp::GPUImageDilationFilter::getCanonicalName() const {
    return JAVA_DILATION_FILTER;
}

void ben::ngp::GPUImageDilationFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "radius", kTypeInt);
    cacheConstructor(env);
    cacheMethod(env, "getRadius", kTypeInt, NULL);
    cacheMethod(env, "setRadius", kTypeVoid, kTypeInt, NULL);
    merge(this);
}

void ben::ngp::GPUImageDilationFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("radius", kTypeFloat, &radius);

}

int ben::ngp::GPUImageDilationFilter::getRadius() const {
    return radius;
}

void ben::ngp::GPUImageDilationFilter::setRadius(int radius) {
    GPUImageDilationFilter::radius = radius;
}
