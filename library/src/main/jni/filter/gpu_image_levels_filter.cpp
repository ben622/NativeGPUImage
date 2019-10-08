//
// Created by ben622 on 2019/10/8.
//

#include "gpu_image_levels_filter.hpp"

ben::ngp::GPUImageLevelsFilter::GPUImageLevelsFilter(JNIEnv *env) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, LEVELS_FRAGMET_SHADER, env) {
    initialize(env);
    this->min = new float[3]{
            minV1, minV2, minV3
    };
    this->mid = new float[3]{
            midV1, midV2, midV3
    };

    this->max = new float[3]{
            maxV1, maxV2, maxV3
    };
    this->minOutput = new float[3]{
            minOutputV1, minOutputV2, minOutputV3
    };
    this->maxOutput = new float[3]{
            maxOutputV1, maxOutputV2, maxOutputV3
    };
}

ben::ngp::GPUImageLevelsFilter::GPUImageLevelsFilter() : GPUImageFilter(NO_FILTER_VERTEX_SHADER,
                                                                        LEVELS_FRAGMET_SHADER) {
    this->min = new float[3]{
            minV1, minV2, minV3
    };
    this->mid = new float[3]{
            midV1, midV2, midV3
    };

    this->max = new float[3]{
            maxV1, maxV2, maxV3
    };
    this->minOutput = new float[3]{
            minOutputV1, minOutputV2, minOutputV3
    };
    this->maxOutput = new float[3]{
            maxOutputV1, maxOutputV2, maxOutputV3
    };
}

void ben::ngp::GPUImageLevelsFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "minV1", kTypeFloat);
    cacheField(env, "minV2", kTypeFloat);
    cacheField(env, "minV3", kTypeFloat);
    cacheField(env, "midV1", kTypeFloat);
    cacheField(env, "midV2", kTypeFloat);
    cacheField(env, "midV3", kTypeFloat);
    cacheField(env, "maxV1", kTypeFloat);
    cacheField(env, "maxV2", kTypeFloat);
    cacheField(env, "maxV3", kTypeFloat);
    cacheField(env, "minOutputV1", kTypeFloat);
    cacheField(env, "minOutputV2", kTypeFloat);
    cacheField(env, "minOutputV3", kTypeFloat);
    cacheField(env, "maxOutputV1", kTypeFloat);
    cacheField(env, "maxOutputV2", kTypeFloat);
    cacheField(env, "maxOutputV3", kTypeFloat);
    cacheField(env, "min", kTypeFloat);
    cacheField(env, "mid", kTypeFloat);
    cacheField(env, "max", kTypeFloat);
    cacheField(env, "minOut", kTypeFloat);
    cacheField(env, "maxOut", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getMinV1", kTypeFloat, NULL);
    cacheMethod(env, "setMinV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMinV2", kTypeFloat, NULL);
    cacheMethod(env, "setMinV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMinV3", kTypeFloat, NULL);
    cacheMethod(env, "setMinV3", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMidV1", kTypeFloat, NULL);
    cacheMethod(env, "setMidV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMidV2", kTypeFloat, NULL);
    cacheMethod(env, "setMidV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMidV3", kTypeFloat, NULL);
    cacheMethod(env, "setMidV3", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxV1", kTypeFloat, NULL);
    cacheMethod(env, "setMaxV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxV2", kTypeFloat, NULL);
    cacheMethod(env, "setMaxV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxV3", kTypeFloat, NULL);
    cacheMethod(env, "setMaxV3", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMinOutputV1", kTypeFloat, NULL);
    cacheMethod(env, "setMinOutputV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMinOutputV2", kTypeFloat, NULL);
    cacheMethod(env, "setMinOutputV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMinOutputV3", kTypeFloat, NULL);
    cacheMethod(env, "setMinOutputV3", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxOutputV1", kTypeFloat, NULL);
    cacheMethod(env, "setMaxOutputV1", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxOutputV2", kTypeFloat, NULL);
    cacheMethod(env, "setMaxOutputV2", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxOutputV3", kTypeFloat, NULL);
    cacheMethod(env, "setMaxOutputV3", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMin", kTypeFloat, NULL);
    cacheMethod(env, "setMin", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMid", kTypeFloat, NULL);
    cacheMethod(env, "setMid", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMax", kTypeFloat, NULL);
    cacheMethod(env, "setMax", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMinOut", kTypeFloat, NULL);
    cacheMethod(env, "setMinOut", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getMaxOut", kTypeFloat, NULL);
    cacheMethod(env, "setMaxOut", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageLevelsFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("minV1", kTypeFloat, &minV1);
    mapField("minV2", kTypeFloat, &minV2);
    mapField("minV3", kTypeFloat, &minV3);
    mapField("midV1", kTypeFloat, &midV1);
    mapField("midV2", kTypeFloat, &midV2);
    mapField("midV3", kTypeFloat, &midV3);
    mapField("maxV1", kTypeFloat, &maxV1);
    mapField("maxV2", kTypeFloat, &maxV2);
    mapField("maxV3", kTypeFloat, &maxV3);
    mapField("minOutputV1", kTypeFloat, &minOutputV1);
    mapField("minOutputV2", kTypeFloat, &minOutputV2);
    mapField("minOutputV3", kTypeFloat, &minOutputV3);
    mapField("maxOutputV1", kTypeFloat, &maxOutputV1);
    mapField("maxOutputV2", kTypeFloat, &maxOutputV2);
    mapField("maxOutputV3", kTypeFloat, &maxOutputV3);
    mapField("min", kTypeFloat, &nMin);
    mapField("mid", kTypeFloat, &nMid);
    mapField("max", kTypeFloat, &nMax);
    mapField("minOut", kTypeFloat, &nMinOut);
    mapField("maxOut", kTypeFloat, &nMaxOut);
}

const char *ben::ngp::GPUImageLevelsFilter::getCanonicalName() const {
    return JAVA_LEVELS_FILTER;
}

void ben::ngp::GPUImageLevelsFilter::onInit() {
    GPUImageFilter::onInit();
    minLocation = glGetUniformLocation(getGlProgId(), "levelMinimum");
    midLocation = glGetUniformLocation(getGlProgId(), "levelMiddle");
    maxLocation = glGetUniformLocation(getGlProgId(), "levelMaximum");
    minOutputLocation = glGetUniformLocation(getGlProgId(), "minOutput");
    maxOutputLocation = glGetUniformLocation(getGlProgId(), "maxOutput");
}

void ben::ngp::GPUImageLevelsFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setMin(nMin, nMid, nMax, nMinOut, nMaxOut);
    updateUniforms();
}


void ben::ngp::GPUImageLevelsFilter::updateUniforms() {
    setFloatVec3(minLocation, min);
    setFloatVec3(midLocation, mid);
    setFloatVec3(maxLocation, max);
    setFloatVec3(minOutputLocation, minOutput);
    setFloatVec3(maxOutputLocation, maxOutput);
}

void ben::ngp::GPUImageLevelsFilter::setMin(float min, float mid, float max, float minOut,
                                            float maxOut) {
    setRedMin(min, mid, max, minOut, maxOut);
    setGreenMin(min, mid, max, minOut, maxOut);
    setBlueMin(min, mid, max, minOut, maxOut);

}

void ben::ngp::GPUImageLevelsFilter::setMin(float min, float mid, float max) {
    setMin(min, mid, max, 0.0f, 1.0f);
}

void ben::ngp::GPUImageLevelsFilter::setRedMin(float min, float mid, float max, float minOut,
                                               float maxOut) {
    this->min[0] = min;
    this->mid[0] = mid;
    this->max[0] = max;
    minOutput[0] = minOut;
    maxOutput[0] = maxOut;
    updateUniforms();

}

void ben::ngp::GPUImageLevelsFilter::setRedMin(float min, float mid, float max) {
    setRedMin(min, mid, max, 0, 1);
}

void ben::ngp::GPUImageLevelsFilter::setGreenMin(float min, float mid, float max, float minOut,
                                                 float maxOut) {
    this->min[1] = min;
    this->mid[1] = mid;
    this->max[1] = max;
    minOutput[1] = minOut;
    maxOutput[1] = maxOut;
    updateUniforms();
}

void ben::ngp::GPUImageLevelsFilter::setGreenMin(float min, float mid, float max) {
    setGreenMin(min, mid, max, 0, 1);
}

void ben::ngp::GPUImageLevelsFilter::setBlueMin(float min, float mid, float max, float minOut,
                                                float maxOut) {
    this->min[2] = min;
    this->mid[2] = mid;
    this->max[2] = max;
    minOutput[2] = minOut;
    maxOutput[2] = maxOut;
    updateUniforms();
}

void ben::ngp::GPUImageLevelsFilter::setBlueMin(float min, float mid, float max) {
    setBlueMin(min, mid, max, 0, 1);
}
