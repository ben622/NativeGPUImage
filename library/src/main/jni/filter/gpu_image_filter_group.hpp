//
// Created by ben622 on 2019/9/16.
//

#ifndef NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP
#define NATIVEGPUIMAGE_GPU_IMAGE_FILTER_GROUP_HPP

#include "gpu_image_filter.hpp"
#include <vector>

using namespace ben::jni;
namespace ben {
    namespace ngp {
        class GPUImageFilterGroup : public ben::ngp::GPUImageFilter {
        private:
            std::vector<ben::ngp::GPUImageFilter*> filters;
            std::vector<ben::ngp::GPUImageFilter*> mergedFilters;
            int *frameBuffers = NULL;
            int frameBuffersSize = 0;
            int *frameBufferTextures = NULL;
            int frameBufferTexturesSize = 0;

            float *glCubeBufferPtr;
            float *glTextureBufferPtr;
            float *glTextureFlipBufferPtr;
        public:
            virtual const char *getCanonicalName() const override;

        public:
            void onOutputSizeChanged(int width, int height);

            void onInit();

            void onInitialized() override;

            void onDestory();

            void
            onDraw(int textureId,  float* cubeBufferPtr,  float *textureBufferPtr);

        public:

            GPUImageFilterGroup();

            GPUImageFilterGroup(char *vertexShader, char *fragmentShader);

            GPUImageFilterGroup(char *vertexShader, char *fragmentShader,JNIEnv *env);

            GPUImageFilterGroup(const std::vector<GPUImageFilter*> &filters);

            GPUImageFilterGroup(JNIEnv *env);

            void updateMergedFilters();

            void destroyFramebuffers();


            void addFilter(GPUImageFilter* aFilter);

            void clearFilter();

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
