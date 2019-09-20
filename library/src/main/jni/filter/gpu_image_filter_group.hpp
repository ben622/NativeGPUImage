//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP

#include "../include/jni/JniHelpers.h"
#include "gpu_image_filter.hpp"
#include <vector>

using namespace ben::jni;
namespace ben {
    namespace ngp {
        class GPUImageFilterGroup : public ben::ngp::GPUImageFilter {
        private:
            std::vector<ben::ngp::GPUImageFilter*> filters;
            std::vector<ben::ngp::GPUImageFilter*> mergedFilters;
            int *frameBuffers;
            int frameBuffersSize;
            int *frameBufferTextures;
            int frameBufferTexturesSize;

            float *glCubeBufferPtr;
            float *glTextureBufferPtr;
            float *glTextureFlipBufferPtr;


        public:
            void onOutputSizeChanged(int width, int height);

            void onInit();

            void onDestory();

            void
            onDraw(int textureId,  float* cubeBufferPtr,  float *textureBufferPtr);

        public:

            GPUImageFilterGroup();

            GPUImageFilterGroup(char *vertexShader, char *fragmentShader);

            GPUImageFilterGroup(const std::vector<GPUImageFilter*> &filters);

            void updateMergedFilters();

            void destroyFramebuffers();

            void addFilter(GPUImageFilter* aFilter);

            const vector<GPUImageFilter *> &getFilters() const;

            void setFilters(const vector<GPUImageFilter *> &filters);

            const vector<GPUImageFilter *> &getMergedFilters() const;

            void setMergedFilters(const vector<GPUImageFilter *> &mergedFilters);

            int *getFrameBuffers() const;

            void setFrameBuffers(int *frameBuffers);

            int *getFrameBufferTextures() const;

            void setFrameBufferTextures(int *frameBufferTextures);

            int getFrameBuffersSize() const;

            void setFrameBuffersSize(int frameBuffersSize);

            int getFrameBufferTexturesSize() const;

            void setFrameBufferTexturesSize(int frameBufferTexturesSize);

            float *getGlCubeBufferPtr() const;

            float *getGlTextureBufferPtr() const;

            float *getGlTextureFlipBufferPtr() const;
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP
