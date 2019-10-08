//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_rgb_dilation_filter.hpp"

ben::ngp::GPUImageRGBDilationFilter::GPUImageRGBDilationFilter(JNIEnv *env)
        : GPUImageTwoPassTextureSamplingFilter(RGB_DILATION_VERTEX_SHADER_1, RGB_DILATION_FRAGMENT_SHADER_1,
                                               RGB_DILATION_VERTEX_SHADER_1, RGB_DILATION_FRAGMENT_SHADER_1, env) {
    initialize(env);
}

const char *ben::ngp::GPUImageRGBDilationFilter::getCanonicalName() const {
    return JAVA_RGB_DILATION_FILTER;
}

void ben::ngp::GPUImageRGBDilationFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "radius", kTypeInt);
    cacheConstructor(env);
    cacheMethod(env, "getRadius", kTypeInt, NULL);
    cacheMethod(env, "setRadius", kTypeVoid, kTypeInt, NULL);
    merge(this);
}

void ben::ngp::GPUImageRGBDilationFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("radius", kTypeInt, &radius);
}

int ben::ngp::GPUImageRGBDilationFilter::getRadius() const {
    return radius;
}

void ben::ngp::GPUImageRGBDilationFilter::switchShader() {
    clearFilter();
    switch (radius) {
        case 0:
        case 1:
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_1, RGB_DILATION_FRAGMENT_SHADER_1));
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_1, RGB_DILATION_FRAGMENT_SHADER_1));
        case 2:
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_2, RGB_DILATION_FRAGMENT_SHADER_2));
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_2, RGB_DILATION_FRAGMENT_SHADER_2));
        case 3:
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_3, RGB_DILATION_FRAGMENT_SHADER_3));
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_3, RGB_DILATION_FRAGMENT_SHADER_3));
        default:
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_4, RGB_DILATION_FRAGMENT_SHADER_4));
            addFilter(new GPUImageFilter(RGB_DILATION_VERTEX_SHADER_4, RGB_DILATION_FRAGMENT_SHADER_4));
    }

}
