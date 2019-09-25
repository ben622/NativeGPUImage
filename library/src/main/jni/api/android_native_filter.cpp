//
// Created by ben622 on 2019/9/25.
//

#include "android_native_filter.hpp"

ben::ngp::NativeFilter::NativeFilter() {}

ben::ngp::NativeFilter::NativeFilter(JNIEnv *env) : JavaClass(env) {
    initialize(env);
    merge(this);
}

void ben::ngp::NativeFilter::initialize(JNIEnv *env) {
    setClass(env);
    cacheField(env, "filterType", kTypeInt);
    cacheConstructor(env);
    cacheMethod(env, "getFilterType", kTypeInt, NULL);
    cacheMethod(env, "setFilterType", kTypeVoid, kTypeInt, NULL);
}

void ben::ngp::NativeFilter::mapFields() {
    mapField("filterType", kTypeFloat, &filterType);
}

const char *ben::ngp::NativeFilter::getCanonicalName() const {
    return JAVA_NATIVE_FILTER;
}

int ben::ngp::NativeFilter::getFilterType() const {
    return filterType;
}

void ben::ngp::NativeFilter::setFilterType(int filterType) {
    NativeFilter::filterType = filterType;
}
