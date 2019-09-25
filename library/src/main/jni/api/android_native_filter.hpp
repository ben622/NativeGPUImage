//
// Created by ben622 on 2019/9/25.
//

#ifndef NATIVEGPUIMAGE_ANDROID_NATIVE_FILTER_HPP
#define NATIVEGPUIMAGE_ANDROID_NATIVE_FILTER_HPP
#include "../include/jni/JniHelpers.h"
#include "../util/filter_type.hpp"
#define JAVA_NATIVE_FILTER "com/ben/android/library/filter/NativeFilter"

using namespace ben::jni;
namespace ben{
    namespace ngp{
        class NativeFilter : public JavaClass{
        private:
            int filterType;
        public:
            NativeFilter();

            NativeFilter(JNIEnv *env);

            void initialize(JNIEnv *env) override;

            void mapFields() override;

            const char *getCanonicalName() const override;

        public:
            int getFilterType() const;

            void setFilterType(int filterType);
        };
    }
}
#endif //NATIVEGPUIMAGE_ANDROID_NATIVE_FILTER_HPP
