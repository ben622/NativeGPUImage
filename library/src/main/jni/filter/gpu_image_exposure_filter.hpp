//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_EXPOSURE_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_EXPOSURE_FILTER_HPP

#include "gpu_image_filter.hpp"

#define JAVA_EXPOSURE_FILTER "com/ben/android/library/filter/GPUImageExposureFilter"
static char *EXPOSURE_FRAGMENT_SHADER = GET_STR(
        varying
        highp
        vec2 textureCoordinate;

        uniform
        sampler2D inputImageTexture;
        uniform
        highp float exposure;

        void main() {
            highp
            vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);

            gl_FragColor = vec4(textureColor.rgb * pow(2.0, exposure), textureColor.w);
        }
);
namespace ben {
    namespace ngp {
        class GPUImageExposureFilter : public GPUImageFilter {
        private:
            int exposureLocation;
            float exposure;
        public:
            GPUImageExposureFilter();

            GPUImageExposureFilter(JNIEnv *env);

            virtual void onInit();

            virtual void onInitialized();

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            void setExposure(float exposure);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_EXPOSURE_FILTER_HPP
