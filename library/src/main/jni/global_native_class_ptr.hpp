//
// Created by ben622 on 2019/9/18.
//
#pragma once
#ifndef LIVE_GLOBAL_NATIVE_CLASS_PTR_HPP
#define LIVE_GLOBAL_NATIVE_CLASS_PTR_HPP

#include "include/jni/JniHelpers.h"
using namespace ben::jni;
namespace ben{
    namespace ngp{
        extern ClassRegistry *classRegistryPtr;;
    }
}
#endif //LIVE_GLOBAL_NATIVE_CLASS_PTR_HPP
