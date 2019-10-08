//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPUIMAGEHALFTONEFILTER_HPP
#define NATIVEGPUIMAGE_GPUIMAGEHALFTONEFILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_HALFTONE_FILTER "com/ben/android/library/filter/GPUImageHalftoneFilter"
static char *HALFTONE_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;

        uniform highp float fractionalWidthOfPixel;
        uniform highp float aspectRatio;

        const highp vec3 W = vec3(0.2125, 0.7154, 0.0721);

        void main()
        {
            highp vec2 sampleDivisor = vec2(fractionalWidthOfPixel, fractionalWidthOfPixel / aspectRatio);
            highp vec2 samplePos = textureCoordinate - mod(textureCoordinate, sampleDivisor) + 0.5 * sampleDivisor;
            highp vec2 textureCoordinateToUse = vec2(textureCoordinate.x, (textureCoordinate.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
            highp vec2 adjustedSamplePos = vec2(samplePos.x, (samplePos.y * aspectRatio + 0.5 - 0.5 * aspectRatio));
            highp float distanceFromSamplePoint = distance(adjustedSamplePos, textureCoordinateToUse);
            lowp vec3 sampledColor = texture2D(inputImageTexture, samplePos).rgb;
            highp float dotScaling = 1.0 - dot(sampledColor, W);
            lowp float checkForPresenceWithinDot = 1.0 - step(distanceFromSamplePoint, (fractionalWidthOfPixel * 0.5) * dotScaling);
            gl_FragColor = vec4(vec3(checkForPresenceWithinDot), 1.0);
        }
);

namespace ben{
    namespace ngp{
        class GPUImageHalftoneFilter:public GPUImageFilter{
        private:
            int fractionalWidthOfPixelLocation;
            int aspectRatioLocation;
            float fractionalWidthOfAPixel;
            float aspectRatio;
        public:
            GPUImageHalftoneFilter();

            GPUImageHalftoneFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setFractionalWidthOfAPixel(float fractionalWidthOfAPixel);

            void setAspectRatio(float aspectRatio);

            void onOutputSizeChanged(int width, int height) override;

        };
    }
}
#endif //NATIVEGPUIMAGE_GPUIMAGEHALFTONEFILTER_HPP
