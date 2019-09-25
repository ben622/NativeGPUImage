//
// Created by ben622 on 2019/9/17.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_TWO_PASS_TEXTURE_SAMPLING_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_TWO_PASS_TEXTURE_SAMPLING_FILTER_HPP

#include "gpu_image_two_pass_filter.hpp"

namespace ben {
    namespace ngp {
        class GPUImageTwoPassTextureSamplingFilter : public GPUImageTwoPassFilter {
        public:
            GPUImageTwoPassTextureSamplingFilter(char *firstVertexShader, char *firstFragmentShader,
                                                 char *secondVertexShader,
                                                 char *secondFragmentShader,
                                                 JNIEnv *env);
            GPUImageTwoPassTextureSamplingFilter(char *firstVertexShader, char *firstFragmentShader,
                                                 char *secondVertexShader,
                                                 char *secondFragmentShader);

            void onOutputSizeChanged(int width, int height) override ;

            void onInit() override ;

            virtual float getVerticalTexelOffsetRatio();

            virtual float getHorizontalTexelOffsetRatio();

            void initTexelOffsets();

        public:
            virtual const char *getCanonicalName() const override;
        };
    }
}
#endif //NATIVEGPUIMAGE_GPU_IMAGE_TWO_PASS_TEXTURE_SAMPLING_FILTER_HPP
