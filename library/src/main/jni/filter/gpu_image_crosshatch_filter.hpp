//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_CROSSHATCH_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_CROSSHATCH_FILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_CROSSHATCH_FILTER "com/ben/android/library/filter/GPUImageCrosshatchFilter"
static char *CROSSHATCH_FRAGMENT_SHADER = GET_STR(
        varying
        highp
        vec2 textureCoordinate;
        uniform
        sampler2D inputImageTexture;
        uniform
        highp float crossHatchSpacing;
        uniform
        highp float lineWidth;
        const highp vec3
        W = vec3(0.2125, 0.7154, 0.0721);
        void main() {
            highp float luminance = dot(texture2D(inputImageTexture, textureCoordinate).rgb, W);
            lowp
            vec4 colorToDisplay = vec4(1.0, 1.0, 1.0, 1.0);
            if (luminance < 1.00) {
                if (mod(textureCoordinate.x + textureCoordinate.y, crossHatchSpacing) <=
                    lineWidth) {
                    colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
                }
            }
            if (luminance < 0.75) {
                if (mod(textureCoordinate.x - textureCoordinate.y, crossHatchSpacing) <=
                    lineWidth) {
                    colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
                }
            }
            if (luminance < 0.50) {
                if (mod(textureCoordinate.x + textureCoordinate.y - (crossHatchSpacing / 2.0),
                        crossHatchSpacing) <= lineWidth) {
                    colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
                }
            }
            if (luminance < 0.3) {
                if (mod(textureCoordinate.x - textureCoordinate.y - (crossHatchSpacing / 2.0),
                        crossHatchSpacing) <= lineWidth) {
                    colorToDisplay = vec4(0.0, 0.0, 0.0, 1.0);
                }
            }
            gl_FragColor = colorToDisplay;
        }
);

namespace ben{
    namespace ngp{
        class GPUImageCrosshatchFilter:public GPUImageFilter{
        private:
            float crossHatchSpacing;
            int crossHatchSpacingLocation;
            float lineWidth;
            int lineWidthLocation;
        public:
            GPUImageCrosshatchFilter();

            GPUImageCrosshatchFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setCrossHatchSpacing(float crossHatchSpacing);

            void setLineWidth(float lineWidth);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_CROSSHATCH_FILTER_HPP
