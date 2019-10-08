//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_SOLARIZE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_SOLARIZE_FILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_SOLARIZE_FILTER "com/ben/android/library/filter/GPUImageSolarizeFilter"
static char *SOLATIZE_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform highp float threshold;

        const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

        void main()
        {
            highp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            highp float luminance = dot(textureColor.rgb, W);
            highp float thresholdResult = step(luminance, threshold);
            highp vec3 finalColor = abs(thresholdResult - textureColor.rgb);

            gl_FragColor = vec4(finalColor, textureColor.w);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageSolarizeFilter:public GPUImageFilter{
        private:
            int uniformThresholdLocation;
            float threshold;
        public:
            GPUImageSolarizeFilter();

            GPUImageSolarizeFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setThreshold(float threshold);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_SOLARIZE_FILTER_HPP
