//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_ALPHA_BLEND_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_ALPHA_BLEND_FILTER_HPP

#include "gpu_image_mix_blend_filter.hpp"
#define JAVA_ALPHA_BLEND_FILTER "com/ben/android/library/filter/GPUImageAlphaBlendFilter"
static char *ALPHA_BLEND_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;
        varying highp vec2 textureCoordinate2;

        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture2;

        uniform lowp float mixturePercent;

        void main()
        {
            lowp vec4 textureColor = texture2D(inputImageTexture, textureCoordinate);
            lowp vec4 textureColor2 = texture2D(inputImageTexture2, textureCoordinate2);

            gl_FragColor = vec4(mix(textureColor.rgb, textureColor2.rgb, textureColor2.a * mixturePercent), textureColor.a);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageAlphaBlendFilter:public GPUImageMixBlendFilter {
        public:
            GPUImageAlphaBlendFilter(JNIEnv *env);
            GPUImageAlphaBlendFilter(float mix,JNIEnv *env);

            virtual void initialize(JNIEnv *env);

            virtual void mapFields();

            virtual const char *getCanonicalName() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_ALPHA_BLEND_FILTER_HPP
