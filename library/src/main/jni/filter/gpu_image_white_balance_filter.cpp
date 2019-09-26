//
// Created by ben622 on 2019/9/26.
//

#include "gpu_image_white_balance_filter.hpp"

ben::ngp::GPUImageWhiteBalanceFilter::GPUImageWhiteBalanceFilter(JNIEnv *env) : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, WHITE_BALANCE_FRAGMENT_SHADER, env) {
    initialize(env);
    this->temperature = 5000.0f;
    this->tint = 0.0f;
}

ben::ngp::GPUImageWhiteBalanceFilter::GPUImageWhiteBalanceFilter() : GPUImageFilter(
        NO_FILTER_VERTEX_SHADER, WHITE_BALANCE_FRAGMENT_SHADER) {
    this->temperature = 5000.0f;
    this->tint = 0.0f;
}
ben::ngp::GPUImageWhiteBalanceFilter::GPUImageWhiteBalanceFilter(
        float temperature, float tint)
        : GPUImageFilter(NO_FILTER_VERTEX_SHADER, WHITE_BALANCE_FRAGMENT_SHADER), temperature(temperature), tint(tint) {

}

void ben::ngp::GPUImageWhiteBalanceFilter::onInit() {
    GPUImageFilter::onInit();
    temperatureLocation = glGetUniformLocation(getGlProgId(), "temperature");
    tintLocation = glGetUniformLocation(getGlProgId(), "tint");
}

void ben::ngp::GPUImageWhiteBalanceFilter::onInitialized() {
    GPUImageFilter::onInitialized();
    setTemperature(temperature);
    setTint(tint);
}

void ben::ngp::GPUImageWhiteBalanceFilter::initialize(JNIEnv *env) {
    GPUImageFilter::initialize(env);
    cacheField(env, "temperature", kTypeFloat);
    cacheField(env, "tint", kTypeFloat);
    cacheConstructor(env);
    cacheMethod(env, "getTemperature", kTypeFloat, NULL);
    cacheMethod(env, "setTemperature", kTypeVoid, kTypeFloat, NULL);
    cacheMethod(env, "getTint", kTypeFloat, NULL);
    cacheMethod(env, "setTint", kTypeVoid, kTypeFloat, NULL);
    merge(this);
}

void ben::ngp::GPUImageWhiteBalanceFilter::mapFields() {
    GPUImageFilter::mapFields();
    mapField("temperature", kTypeFloat, &temperature);
    mapField("tint", kTypeFloat, &tint);
}

const char *ben::ngp::GPUImageWhiteBalanceFilter::getCanonicalName() const {
    return JAVA_WHITE_BALANCE_FILTER;
}

int ben::ngp::GPUImageWhiteBalanceFilter::getTemperatureLocation() const {
    return temperatureLocation;
}

void ben::ngp::GPUImageWhiteBalanceFilter::setTemperatureLocation(int temperatureLocation) {
    GPUImageWhiteBalanceFilter::temperatureLocation = temperatureLocation;
}

float ben::ngp::GPUImageWhiteBalanceFilter::getTemperature() const {
    return temperature;
}

void ben::ngp::GPUImageWhiteBalanceFilter::setTemperature(float temperature) {
    GPUImageWhiteBalanceFilter::temperature = temperature;
    //setFloat(temperatureLocation, this->temperature < 5000 ? (float) (0.0004 * (this->temperature - 5000.0)) : (float) (0.00006 * (this->temperature - 5000.0)));
    setFloat(temperatureLocation, -1.2f);
}

int ben::ngp::GPUImageWhiteBalanceFilter::getTintLocation() const {
    return tintLocation;
}

void ben::ngp::GPUImageWhiteBalanceFilter::setTintLocation(int tintLocation) {
    GPUImageWhiteBalanceFilter::tintLocation = tintLocation;
}

float ben::ngp::GPUImageWhiteBalanceFilter::getTint() const {
    return tint;
}

void ben::ngp::GPUImageWhiteBalanceFilter::setTint(float tint) {
    GPUImageWhiteBalanceFilter::tint = tint;
    //setFloat(tintLocation, (float) (this->tint / 100.0));
    setFloat(tintLocation, 0.0f);
}

