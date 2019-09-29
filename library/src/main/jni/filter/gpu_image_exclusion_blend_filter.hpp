//
// Created by ben622 on 2019/9/29.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_EXCLUSION_BLEND_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_EXCLUSION_BLEND_FILTER_HPP

#include "gpu_image_two_input_filter.hpp"
#define JAVA_EXCLUSION_BLEND_FILTER "com/ben/android/library/filter/GPUImageExclusionBlendFilter"
static char *EXCLUSION_BLEND_FRAGMENT_SHADER = GET_STR(
        varying highp vec2 textureCoordinate;
        varying highp vec2 textureCoordinate2;

        uniform sampler2D inputImageTexture;
        uniform sampler2D inputImageTexture2;

        void main()
        {
            mediump vec4 base = texture2D(inputImageTexture, textureCoordinate);
            mediump vec4 overlay = texture2D(inputImageTexture2, textureCoordinate2);

            //     Dca = (Sca.Da + Dca.Sa - 2.Sca.Dca) + Sca.(1 - Da) + Dca.(1 - Sa)

            gl_FragColor = vec4((overlay.rgb * base.a + base.rgb * overlay.a - 2.0 * overlay.rgb * base.rgb) + overlay.rgb * (1.0 - base.a) + base.rgb * (1.0 - overlay.a), base.a);
        }
);
namespace ben{
    namespace ngp{
        class GPUImageExclusionBlendFilter:public GPUImageTwoInputFilter{
        public:
            GPUImageExclusionBlendFilter();
            GPUImageExclusionBlendFilter(JNIEnv *env);

            virtual const char *getCanonicalName() const;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_EXCLUSION_BLEND_FILTER_HPP
