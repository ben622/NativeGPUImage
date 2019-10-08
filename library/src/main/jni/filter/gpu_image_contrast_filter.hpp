//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_CONTRAST_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_CONTRAST_FILTER_HPP

#include "gpu_image_filter.hpp"
#include "../include/jni/JniHelpersCommon.h"

#define JAVA_CONTRAST_FILTER "com/ben/android/library/filter/GPUImageContrastFilter"
static char *CONTRAST_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform lowp float contrast;

        void main()
        {
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            gl_FragColor = vec4(((textureColor.rgb - vec3(0.5)) * contrast + vec3(0.5)), textureColor.w);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageContrastFilter:public GPUImageFilter{
        private:
            int contrastLocation;
            float contrast;
        public:
            GPUImageContrastFilter();

            GPUImageContrastFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setContrast(float contrast);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_CONTRAST_FILTER_HPP
