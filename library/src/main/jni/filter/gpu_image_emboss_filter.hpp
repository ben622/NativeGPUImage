//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_EMBOSS_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_EMBOSS_FILTER_HPP

#include "gpu_image_3x3_convolution_filter.hpp"

#define JAVA_EMBOSS_FILTER "com/ben/android/library/filter/GPUImageEmbossFilter"

namespace ben{
    namespace ngp{
        class GPUImageEmbossFilter:public GPUImage3x3ConvolutionFilter {
        private:
            float intensity;

        public:
            GPUImageEmbossFilter();
            GPUImageEmbossFilter(JNIEnv *env);

            virtual void onInit();

            virtual void onInitialized();

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            void setIntensity(float intensity);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_EMBOSS_FILTER_HPP
