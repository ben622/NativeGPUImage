//
// Created by ben622 on 2019/10/8.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_MONOCHROME_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_MONOCHROME_FILTER_HPP

#include "gpu_image_filter.hpp"
#define JAVA_MONOCHROME_FILTER "com/ben/android/library/filter/GPUImageMonochromeFilter"
static char *MONOCHROME_FRAGMENT_SHADER = GET_STR(
        precision lowp float;

        varying highp vec2 textureCoordinate;

        uniform sampler2D inputImageTexture;
        uniform float intensity;
        uniform vec3 filterColor;

        const mediump vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

        void main()
        {
            //desat, then apply overlay blend
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            float luminance = dot(textureColor.rgb, luminanceWeighting);

            lowp vec4 desat = vec4(vec3(luminance), 1.0);

            //overlay
            lowp vec4 outputColor = vec4(
                    (desat.r < 0.5 ? (2.0 * desat.r * filterColor.r) : (1.0 - 2.0 * (1.0 - desat.r) * (1.0 - filterColor.r))),
                    (desat.g < 0.5 ? (2.0 * desat.g * filterColor.g) : (1.0 - 2.0 * (1.0 - desat.g) * (1.0 - filterColor.g))),
                    (desat.b < 0.5 ? (2.0 * desat.b * filterColor.b) : (1.0 - 2.0 * (1.0 - desat.b) * (1.0 - filterColor.b))),
                    1.0
            );

            //which is better, or are they equal?
            gl_FragColor = vec4( mix(textureColor.rgb, outputColor.rgb, intensity), textureColor.a);
        }
);

namespace ben{
    namespace ngp{
        class GPUImageMonochromeFilter:public GPUImageFilter{
        private:
            int intensityLocation;
            float intensity = 1.0f;
            int filterColorLocation;
            float *color;

            float v1 = 0.6f;
            float v2 = 0.45f;
            float v3 = 0.3f;

        public:
            GPUImageMonochromeFilter();

            GPUImageMonochromeFilter(JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;

            virtual void onInit();

            virtual void onInitialized();

            void setIntensity(float intensity);

            void setColor(float *color);

        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_MONOCHROME_FILTER_HPP
