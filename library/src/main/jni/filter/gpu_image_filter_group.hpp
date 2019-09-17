//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP

#include "../include/jni/JniHelpers.h"
#include "gpu_image_filter.hpp"
#include <vector>
static float CUBE[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f, 1.0f,
        1.0f, 1.0f,
};
using namespace ben::jni;
namespace ben {
    namespace ngp {
        class GPUImageFilterGroup : public ben::ngp::GPUImageFilter {
        private:
            std::vector<ben::ngp::GPUImageFilter> filters ;
            std::vector<ben::ngp::GPUImageFilter> mergedFilters;
            int *frameBuffers;
            int frameBuffersSize;
            int *frameBufferTextures;
            int frameBufferTexturesSize;
            const void *glCubeBufferPtr;
            const void *glTextureBufferPtr;
            const void *glTextureFlipBufferPtr;

            void onOutputSizeChanged(int width, int height) override;

            void onInit() override;

            void onDestory() override;

            void
            onDraw(int textureId, const void *cubeBufferPtr, const void *textureBufferPtr) override;

        public:

            GPUImageFilterGroup();

            GPUImageFilterGroup(char *vertexShader, char *fragmentShader);

            GPUImageFilterGroup(const std::vector<GPUImageFilter> &filters);

            void updateMergedFilters();

            void destroyFramebuffers();

            void addFilter(GPUImageFilter aFilter);

            const std::vector<GPUImageFilter> &getFilters() const;

            void setFilters(const std::vector<GPUImageFilter> &filters);

            const std::vector<GPUImageFilter> &getMergedFilters() const;

            void setMergedFilters(const std::vector<GPUImageFilter> &mergedFilters);

            int *getFrameBuffers() const;

            void setFrameBuffers(int *frameBuffers);

            int *getFrameBufferTextures() const;

            void setFrameBufferTextures(int *frameBufferTextures);

            const void *getGlCubeBufferPtr() const;

            void setGlCubeBufferPtr(const void *glCubeBufferPtr);

            const void *getGlTextureBufferPtr() const;

            void setGlTextureBufferPtr(const void *glTextureBufferPtr);

            const void *getGlTextureFlipBufferPtr() const;

            void setGlTextureFlipBufferPtr(const void *glTextureFlipBufferPtr);

            int getFrameBuffersSize() const;

            void setFrameBuffersSize(int frameBuffersSize);

            int getFrameBufferTexturesSize() const;

            void setFrameBufferTexturesSize(int frameBufferTexturesSize);
        };
    }
}

#endif //NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP
