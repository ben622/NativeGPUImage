//
// Created by ben622 on 2019/9/17.
//
#ifndef NATIVEGPUIMAGE_GPU_IMAGE_TWO_PASS_FILTER_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_TWO_PASS_FILTER_HPP

#include "gpu_image_filter_group.hpp"

namespace ben {
    namespace ngp {
        class GPUImageTwoPassFilter : public GPUImageFilterGroup {
        public:
            GPUImageTwoPassFilter(char *firstVertexShader, char *firstFragmentShader,
                                  char *secondVertexShader, char *secondFragmentShader,JNIEnv *env);

            GPUImageTwoPassFilter(char *firstVertexShader, char *firstFragmentShader,
                                  char *secondVertexShader, char *secondFragmentShader);

        public:
            virtual const char *getCanonicalName() const override;
        };
    }
}


#endif //NATIVEGPUIMAGE_GPU_IMAGE_TWO_PASS_FILTER_HPP
