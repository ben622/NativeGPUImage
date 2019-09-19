//
// Created by ben622 on 2019/9/16.
//

#include "gpu_image_filter_group.hpp"
#include "../util/textur_rotation_util.hpp"
#include <typeinfo>

using namespace ben::util;
using namespace std;

void ben::ngp::GPUImageFilterGroup::onOutputSizeChanged(int width, int height) {
    GPUImageFilter::onOutputSizeChanged(width, height);
    if (frameBuffers != NULL) {
        destroyFramebuffers();
    }

    int size = filters.size();
    for (int i = 0; i < size; i++) {
        filters[i]->onOutputSizeChanged(width, height);
    }

    if (!mergedFilters.empty()) {
        size = mergedFilters.size();
        frameBuffers = new int[size - 1];
        frameBufferTextures = new int[size - 1];

        for (int i = 0; i < size - 1; i++) {
            glGenFramebuffers(1, reinterpret_cast<GLuint *>(frameBuffers));
            glGenTextures(1, reinterpret_cast<GLuint *>(frameBufferTextures));
            glBindTexture(GL_TEXTURE_2D, frameBufferTextures[i]);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                    GL_RGBA, GL_UNSIGNED_BYTE, NULL);
            glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameterf(GL_TEXTURE_2D,
                    GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers[i]);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                    GL_TEXTURE_2D, frameBufferTextures[i], 0);
        }
    }

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    eglSwapBuffers(getEglDisplay(), getEglSurface());
}

void ben::ngp::GPUImageFilterGroup::onInit() {
    LOGE("%s", "GPUImageFilterGroup onInit");
    GPUImageFilter::onInit();
    for (GPUImageFilter* filter : filters) {
        LOGE("%s","GPUImageFilterGroup init");
        filter->ifNeedInit();
    }
}

void ben::ngp::GPUImageFilterGroup::onDestory() {
    destroyFramebuffers();
    for (GPUImageFilter* filter : filters) {
        filter->destory();
    }
    GPUImageFilter::onDestory();
}

void ben::ngp::GPUImageFilterGroup::onDraw(int textureId, const void *cubeBufferPtr,
                                           const void *textureBufferPtr) {
    LOGE("%s", "GPUImageFilterGroup-->onDraw");
    runPendingOnDrawTasks();
    if (!isIsInitialized() || frameBuffers == NULL || frameBufferTextures == NULL) {
        LOGE("isIsInitialized:%d,frameBuffers:%d,frameBufferTextures:%d", !isIsInitialized(),
             frameBuffers, frameBufferTextures);
        return;
    }
    if (!mergedFilters.empty()) {
        int size = mergedFilters.size();
        int previousTexture = textureId;
        for (int i = 0; i < size; i++) {
            GPUImageFilter* filter = mergedFilters[i];
            bool isNotLast = i < size - 1;
            if (isNotLast) {
                glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers[i]);
                glClearColor(0, 0, 0, 0);
            }

            if (i == 0) {
                filter->onDraw(previousTexture, cubeBufferPtr, textureBufferPtr);
            } else if (i == size - 1) {
                filter->onDraw(previousTexture, glCubeBufferPtr, (size % 2 == 0) ? glTextureFlipBufferPtr : glTextureBufferPtr);
            } else {
                filter->onDraw(previousTexture, glCubeBufferPtr, glTextureBufferPtr);
            }

            if (isNotLast) {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                previousTexture = frameBufferTextures[i];
            }
        }
    }
}

int *ben::ngp::GPUImageFilterGroup::getFrameBuffers() const {
    return frameBuffers;
}

void ben::ngp::GPUImageFilterGroup::setFrameBuffers(int *frameBuffers) {
    GPUImageFilterGroup::frameBuffers = frameBuffers;
}

int *ben::ngp::GPUImageFilterGroup::getFrameBufferTextures() const {
    return frameBufferTextures;
}

void ben::ngp::GPUImageFilterGroup::setFrameBufferTextures(int *frameBufferTextures) {
    GPUImageFilterGroup::frameBufferTextures = frameBufferTextures;
}

const void *ben::ngp::GPUImageFilterGroup::getGlCubeBufferPtr() const {
    return glCubeBufferPtr;
}

void ben::ngp::GPUImageFilterGroup::setGlCubeBufferPtr(const void *glCubeBufferPtr) {
    GPUImageFilterGroup::glCubeBufferPtr = glCubeBufferPtr;
}

const void *ben::ngp::GPUImageFilterGroup::getGlTextureBufferPtr() const {
    return glTextureBufferPtr;
}

void ben::ngp::GPUImageFilterGroup::setGlTextureBufferPtr(const void *glTextureBufferPtr) {
    GPUImageFilterGroup::glTextureBufferPtr = glTextureBufferPtr;
}

const void *ben::ngp::GPUImageFilterGroup::getGlTextureFlipBufferPtr() const {
    return glTextureFlipBufferPtr;
}

void ben::ngp::GPUImageFilterGroup::setGlTextureFlipBufferPtr(const void *glTextureFlipBufferPtr) {
    GPUImageFilterGroup::glTextureFlipBufferPtr = glTextureFlipBufferPtr;
}

int ben::ngp::GPUImageFilterGroup::getFrameBuffersSize() const {
    return frameBuffersSize;
}

void ben::ngp::GPUImageFilterGroup::setFrameBuffersSize(int frameBuffersSize) {
    GPUImageFilterGroup::frameBuffersSize = frameBuffersSize;
}

int ben::ngp::GPUImageFilterGroup::getFrameBufferTexturesSize() const {
    return frameBufferTexturesSize;
}

void ben::ngp::GPUImageFilterGroup::setFrameBufferTexturesSize(int frameBufferTexturesSize) {
    GPUImageFilterGroup::frameBufferTexturesSize = frameBufferTexturesSize;
}


//group 构造函数
ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup(
        const std::vector<ben::ngp::GPUImageFilter*> &filters) : filters(filters) {
    this->filters = filters;
    if (!this->filters.empty()) {
        updateMergedFilters();
    }
    glCubeBufferPtr = CUBE;
    glTextureBufferPtr = TEXTURE_NO_ROTATION;
    glTextureFlipBufferPtr = getRotation(Rotation::NORMAL, false, true);

}


ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup() {
    GPUImageFilterGroup(vector());
}

void ben::ngp::GPUImageFilterGroup::updateMergedFilters() {
    if (this->filters.empty()) {
        return;
    }
    this->mergedFilters.clear();

    std::vector<GPUImageFilter*> filters;
    for (GPUImageFilter* filter : this->filters) {
        if (strcmp(typeid(GPUImageFilterGroup).name(), typeid(filter).name()) == 0) {
            GPUImageFilterGroup *filterGroup = dynamic_cast<GPUImageFilterGroup *>(filter);
            filterGroup->updateMergedFilters();
            filters = filterGroup->getMergedFilters();
            if (filters.empty())
                continue;
            for (int i = 0; i < filters.size(); i++) {
                mergedFilters.push_back(filters[i]);
            }
            continue;
        }
        mergedFilters.push_back(filter);
    }
}

void ben::ngp::GPUImageFilterGroup::destroyFramebuffers() {
    if (frameBufferTextures != NULL) {
        glDeleteTextures(frameBuffersSize, reinterpret_cast<const GLuint *>(frameBufferTextures));
        //remove pointer
        delete frameBufferTextures;
    }
    if (frameBuffers != NULL) {
        glDeleteFramebuffers(frameBuffersSize, reinterpret_cast<const GLuint *>(frameBuffers));
        //remove pointer
        delete frameBuffers;
    }
}

void ben::ngp::GPUImageFilterGroup::addFilter(ben::ngp::GPUImageFilter* aFilter) {
    filters.push_back(aFilter);
    updateMergedFilters();
}

ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup(char *vertexShader, char *fragmentShader)
        : GPUImageFilter(vertexShader, fragmentShader) {

}

const std::vector<ben::ngp::GPUImageFilter *> &ben::ngp::GPUImageFilterGroup::getFilters() const {
    return filters;
}

void ben::ngp::GPUImageFilterGroup::setFilters(const std::vector<ben::ngp::GPUImageFilter *> &filters) {
    GPUImageFilterGroup::filters = filters;
}

const std::vector<ben::ngp::GPUImageFilter *> &ben::ngp::GPUImageFilterGroup::getMergedFilters() const {
    return mergedFilters;
}

void ben::ngp::GPUImageFilterGroup::setMergedFilters(
        const std::vector<ben::ngp::GPUImageFilter *> &mergedFilters) {
    GPUImageFilterGroup::mergedFilters = mergedFilters;
}

