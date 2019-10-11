//
// Created by ben622 on 2019/9/16.
//

#include "gpu_image_filter_group.hpp"
#include "../util/textur_rotation_util.hpp"

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
        frameBuffersSize = size - 1;
        frameBuffers = new int[size - 1];
        frameBufferTexturesSize = size - 1;
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
}

void ben::ngp::GPUImageFilterGroup::onInit() {
    GPUImageFilter::onInit();
    for (GPUImageFilter *filter : filters) {
        filter->ifNeedInit();
    }
}

void ben::ngp::GPUImageFilterGroup::onDestory() {
    destroyFramebuffers();
    for (GPUImageFilter *filter : filters) {
        filter->destory();
    }
    GPUImageFilter::onDestory();
}

void ben::ngp::GPUImageFilterGroup::onDraw(int textureId, float *cubeBufferPtr,
                                           float *textureBufferPtr) {
    runPendingOnDrawTasks();
    if (!isIsFilterInitialized() || frameBuffers == NULL || frameBufferTextures == NULL) {
        LOGE("isFilterInitialized:%d,frameBuffers:%d,frameBufferTextures:%d",
             !isIsFilterInitialized(),
             frameBuffers, frameBufferTextures);
        return;
    }
    if (!mergedFilters.empty()) {
        int size = mergedFilters.size();
        int previousTexture = textureId;
        for (int i = 0; i < size; i++) {
            GPUImageFilter *filter = mergedFilters[i];
            bool isNotLast = i < size - 1;
            if (isNotLast) {
                glBindFramebuffer(GL_FRAMEBUFFER, frameBuffers[i]);
                glClearColor(0, 0, 0, 0);
            }

            if (i == 0) {
                filter->onDraw(previousTexture, cubeBufferPtr, textureBufferPtr);
            } else if (i == size - 1) {
                filter->onDraw(previousTexture, new float[8]{
                        -1.0f, -1.0f,
                        1.0f, -1.0f,
                        -1.0f, 1.0f,
                        1.0f, 1.0f,
                }, (size % 2 == 0) ? glTextureFlipBufferPtr : glTextureBufferPtr);
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

ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup(JNIEnv *env) : GPUImageFilter(env) {
    glCubeBufferPtr = CUBE;
    glTextureBufferPtr = TEXTURE_NO_ROTATION;
    glTextureFlipBufferPtr = getRotation(Rotation::NORMAL, false, true);
}

//group 构造函数
ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup(
        const std::vector<ben::ngp::GPUImageFilter *> &filters) : filters(filters) {
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

    std::vector<GPUImageFilter *> filters;
    for (GPUImageFilter *filter : this->filters) {
        if (dynamic_cast<GPUImageFilterGroup *>(filter) != NULL) {
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
    /*if (frameBufferTextures != NULL) {
        glDeleteTextures(frameBufferTexturesSize, (const GLuint *) frameBufferTextures);
        //remove pointer
        frameBufferTexturesSize = 0;
        delete frameBufferTextures;
    }
    if (frameBuffers != NULL) {
        glDeleteFramebuffers(frameBuffersSize, (const GLuint *) frameBuffers);
        //remove pointer
        frameBuffersSize = 0;
        delete frameBuffers;
    }*/
}

void ben::ngp::GPUImageFilterGroup::addFilter(ben::ngp::GPUImageFilter *aFilter) {
    filters.push_back(aFilter);
    updateMergedFilters();
}

ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup(char *vertexShader, char *fragmentShader)
        : GPUImageFilter(vertexShader, fragmentShader) {

}

ben::ngp::GPUImageFilterGroup::GPUImageFilterGroup(char *vertexShader, char *fragmentShader,
                                                   JNIEnv *env)
        : GPUImageFilter(vertexShader, fragmentShader, env) {

}


const std::vector<ben::ngp::GPUImageFilter *> &ben::ngp::GPUImageFilterGroup::getFilters() const {
    return filters;
}

void
ben::ngp::GPUImageFilterGroup::setFilters(const std::vector<ben::ngp::GPUImageFilter *> &filters) {
    GPUImageFilterGroup::filters = filters;
}

const std::vector<ben::ngp::GPUImageFilter *> &
ben::ngp::GPUImageFilterGroup::getMergedFilters() const {
    return mergedFilters;
}

void ben::ngp::GPUImageFilterGroup::setMergedFilters(
        const std::vector<ben::ngp::GPUImageFilter *> &mergedFilters) {
    GPUImageFilterGroup::mergedFilters = mergedFilters;
}

float *ben::ngp::GPUImageFilterGroup::getGlCubeBufferPtr() const {
    return glCubeBufferPtr;
}

float *ben::ngp::GPUImageFilterGroup::getGlTextureBufferPtr() const {
    return glTextureBufferPtr;
}

float *ben::ngp::GPUImageFilterGroup::getGlTextureFlipBufferPtr() const {
    return glTextureFlipBufferPtr;
}

const char *ben::ngp::GPUImageFilterGroup::getCanonicalName() const {
    return GPUImageFilter::getCanonicalName();
}

void ben::ngp::GPUImageFilterGroup::clearFilter() {
    filters.clear();
    mergedFilters.clear();

}

void ben::ngp::GPUImageFilterGroup::onInitialized() {
    GPUImageFilter::onInitialized();
}



