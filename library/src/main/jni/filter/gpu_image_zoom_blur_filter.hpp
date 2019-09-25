//
// Created by ben622 on 2019/9/21.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_ZOOM_BLUR_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_ZOOM_BLUR_FILTER_HPP
#include "gpu_image_filter.hpp"
#define JAVA_ZOOM_BLUR_FILTER "com/ben/android/library/filter/ZoomBlurFilter"
#define GET_STR(x) #x
static char *ZOOM_BLUR_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;

        uniform highp vec2 blurCenter;
        uniform highp float blurSize;

        void main()
        {
            // TODO: Do a more intelligent scaling based on resolution here
            highp vec2 samplingOffset = 1.0/100.0 * (blurCenter - textureCoordinate) * blurSize;

            lowp vec4 fragmentColor = texture2D(inputImageTexture, textureCoordinate) * 0.18;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate + samplingOffset) * 0.15;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate + (2.0 * samplingOffset)) *  0.12;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate + (3.0 * samplingOffset)) * 0.09;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate + (4.0 * samplingOffset)) * 0.05;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate - samplingOffset) * 0.15;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate - (2.0 * samplingOffset)) *  0.12;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate - (3.0 * samplingOffset)) * 0.09;
            fragmentColor += texture2D(inputImageTexture, textureCoordinate - (4.0 * samplingOffset)) * 0.05;

            gl_FragColor = fragmentColor;
        }
);
namespace ben {
    namespace ngp {
        class GPUImageZoomBlurFilter : public GPUImageFilter {
        private:
            float pointXF;
            float pointYF;
            int blurCenterLocation;
            float blurSize;
            int blurSizeLocation;
        public:
            GPUImageZoomBlurFilter();

            GPUImageZoomBlurFilter(JNIEnv *env);

        public:
            void initialize(JNIEnv *env) override;

            void mapFields() override;

            virtual const char *getCanonicalName() const;

        public:
            virtual void onInit();

            virtual void onInitialized();

        public:
            void setBlurCenter(float pointXF, float pointYF);

            void setBlurSize(int blurSize);
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_ZOOM_BLUR_FILTER_HPP
