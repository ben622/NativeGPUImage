//
// Created by ben622 on 2019/9/16.
//
#include "gpu_image_filter.hpp"
#include "../util/open_gl_util.hpp"
#include "../include/queue.h"
using namespace ben::util;
using namespace ben::ngp;
//filter
GPUImageFilter::GPUImageFilter() {
    GPUImageFilter(const_cast<char *>(NO_FILTER_VERTEX_SHADER),
                   const_cast<char *>(NO_FILTER_FRAGMENT_SHADER));
}

GPUImageFilter::GPUImageFilter(char *vertexShader, char *fragmentShader) {
    this->vertexShader = vertexShader;
    this->fragmentShader = fragmentShader;

    //create queue
    //create_queue()
}



void GPUImageFilter::onInit() {
    glProgId = loadProgram(vertexShader, fragmentShader);
    glAttribPosition = glGetAttribLocation(glProgId, "position");
    glUniformTexture = glGetUniformLocation(glProgId, "inputImageTexture");
    glAttribTextureCoordinate = glGetAttribLocation(glProgId, "inputTextureCoordinate");
    isInitialized = true;
}

void GPUImageFilter::onInitialized() {
    LOGI("%s", "onInitialized");
}

void GPUImageFilter::onDestory() {
    LOGI("%s", "onDestory");
}

void GPUImageFilter::onDraw(int textureId,const void* cubeBufferPtr,const void* textureBufferPtr) {
    glUseProgram(glProgId);
    //runPendingOnDrawTasks();
    if (!isInitialized) {
        return;
    }
    //cubeBuffer.position(0);
    glVertexAttribPointer(glAttribPosition, 2, GL_FLOAT, false, 0, cubeBufferPtr);
    glEnableVertexAttribArray(glAttribPosition);
    //textureBuffer.position(0);
    glVertexAttribPointer(glAttribTextureCoordinate, 2, GL_FLOAT, false, 0,
                          textureBufferPtr);
    glEnableVertexAttribArray(glAttribTextureCoordinate);
    if (textureId != NO_TEXTURE) {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);
        glUniform1i(glUniformTexture, 0);
    }
    onDrawArraysPre();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(glAttribPosition);
    glDisableVertexAttribArray(glAttribTextureCoordinate);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void GPUImageFilter::onOutputSizeChanged(int width, int height) {
    this->outputWidth = width;
    this->outputHeight = height;
}

void GPUImageFilter::destory() {
    isInitialized = false;
    glDeleteProgram(glProgId);
    onDestory();
}

void GPUImageFilter::onDrawArraysPre() {

}

void GPUImageFilter::ifNeedInit() {
    if (!isInitialized){
        onInit();
        onInitialized();
    }
}

