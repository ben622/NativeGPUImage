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

void
GPUImageFilter::onDraw(int textureId, const void *cubeBufferPtr, const void *textureBufferPtr) {
    glUseProgram(glProgId);
    runPendingOnDrawTasks();
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
    if (!isInitialized) {
        onInit();
        onInitialized();
    }
}

void GPUImageFilter::addDrawThread(GL_VARS *glVars) {
    runOnDrawGLVars.push_back(glVars);
}


void GPUImageFilter::setInteger(int location, int intValue) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.intValue = intValue;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_INTEGER;
    addDrawThread(&glVars);
}


void GPUImageFilter::setFloat(int location, float floatValue) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.floatValue = floatValue;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_FLOAT;
    addDrawThread(&glVars);
}

void GPUImageFilter::setFloatVec2(int location, float *arrayValuePtr) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.arrayValuePtr = arrayValuePtr;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_VEC2;
    addDrawThread(&glVars);
}

void GPUImageFilter::setFloatVec3(int location, float *arrayValuePtr) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.arrayValuePtr = arrayValuePtr;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_VEC3;
    addDrawThread(&glVars);
}

void GPUImageFilter::setFloatVec4(int location, float *arrayValuePtr) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.arrayValuePtr = arrayValuePtr;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_VEC4;
    addDrawThread(&glVars);
}

void GPUImageFilter::setFloatArray(int location, float *arrayValuePtr,int arrayValueLength) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.arrayValuePtr = arrayValuePtr;
    glVars.arrayValueLength = arrayValueLength;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_ARRAY;
    addDrawThread(&glVars);
}

void GPUImageFilter::setPoint(int location, float x, float y) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.x = x;
    glVars.y = y;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_POINT;
    addDrawThread(&glVars);
}

void GPUImageFilter::setUniformMatrix3f(int location, float *arrayValuePtr) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.arrayValuePtr = arrayValuePtr;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX3F;
    addDrawThread(&glVars);
}

void GPUImageFilter::setUniformMatrix4f(int location, float *arrayValuePtr) {
    GL_VARS glVars;
    glVars.location = location;
    glVars.arrayValuePtr = arrayValuePtr;
    glVars.filter = this;
    glVars.glDrawType = GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX4F;
    addDrawThread(&glVars);
}

void *onRunDrawGlCallback(void *arg) {
    GL_VARS *glVars = static_cast<GL_VARS *>(arg);
    static_cast<GPUImageFilter *>(glVars->filter)->ifNeedInit();
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_INTEGER) {
        glUniform1i(glVars->location, glVars->intValue);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT) {
        glUniform1f(glVars->location, glVars->floatValue);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_VEC2) {
        glUniform2fv(glVars->location, 1, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_VEC3) {
        glUniform3fv(glVars->location, 1, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_VEC4) {
        glUniform4fv(glVars->location, 1, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_ARRAY) {
        glUniform1fv(glVars->location, glVars->arrayValueLength, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_POINT) {
        float *vec2 = new float[2]{
                glVars->x,
                glVars->y
        };
        glUniform2fv(glVars->location, 1, vec2);
    }

    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX3F) {
        glUniformMatrix3fv(glVars->location, 1, false, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX4F) {
        glUniformMatrix4fv(glVars->location, 1, false, glVars->arrayValuePtr);
    }

}


void GPUImageFilter::runPendingOnDrawTasks() {
    if (this->runOnDrawGLVars.empty()) {
        return;
    }
    for (int i = 0; i < runOnDrawGLVars.size(); i++) {
        //create thread
        pthread_create(runOnDrawGLVars[i]->pthread, NULL, onRunDrawGlCallback, runOnDrawGLVars[i]);
    }

}

