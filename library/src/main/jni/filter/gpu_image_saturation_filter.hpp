//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_SATURATION_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_SATURATION_FILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_SATURATION_FILTER "com/ben/android/library/filter/GPUImageSaturationFilter"
static char *SATURATION_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform lowp float saturation;

        // Values from \Graphics Shaders: Theory and Practice\ by Bailey and Cunningham
        const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

        void main()
        {
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            lowp float luminance = dot(textureColor.rgb, luminanceWeighting);
            lowp vec3 greyScaleColor = vec3(luminance);

            gl_FragColor = vec4(mix(greyScaleColor, textureColor.rgb, saturation), textureColor.w);

        }
);
namespace ben{
    namespace ngp{
        class GPUImageSaturationFilter:public GPUImageFilter{
        private:
            int saturationLocation;
            float saturation;
        public:
            GPUImageSaturationFilter();

            GPUImageSaturationFilter(JNIEnv *env);

            virtual void onInit();

            virtual void onInitialized();

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            void setSaturation(float saturation);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_SATURATION_FILTER_HPP
