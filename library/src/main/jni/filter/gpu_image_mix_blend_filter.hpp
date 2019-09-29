//
// Created by ben622 on 2019/9/29.
//
#ifndef NATIVEGPUIMAGE_GPU_IMAGE_MIX_BLEND_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_MIX_BLEND_FILTER_HPP

#include "gpu_image_two_input_filter.hpp"

#define JAVA_MIX_BLEND_FILTER "com/ben/android/library/filter/GPUImageMixBlendFilter"
namespace ben {
    namespace ngp {
        class GPUImageMixBlendFilter : public GPUImageTwoInputFilter {
        private:
            int mixLocation;
            float mix;
        public:
            GPUImageMixBlendFilter(char *fragmentShader, JNIEnv *env);

            GPUImageMixBlendFilter(char *fragmentShader, JNIEnv *env, float mix);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setMix(float mix);

        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_MIX_BLEND_FILTER_HPP
