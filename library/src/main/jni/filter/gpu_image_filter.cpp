//
// Created by ben622 on 2019/9/16.
//
#include "gpu_image_filter.hpp"
#include "../util/open_gl_util.hpp"
#include "../include/queue.h"
#include <cstring>

using namespace ben::util;
using namespace ben::ngp;

//filter
GPUImageFilter::GPUImageFilter() {
    this->vertexShader = NO_FILTER_VERTEX_SHADER;
    this->fragmentShader = NO_FILTER_FRAGMENT_SHADER;
}

GPUImageFilter::GPUImageFilter(char *vertexShaderArg, char *fragmentShaderArg) {
    this->vertexShader = vertexShaderArg;
    this->fragmentShader = fragmentShaderArg;
}


void GPUImageFilter::onInit() {
    LOGE("%s", "GPUImageFilter onInit");
    glProgId = loadProgram(vertexShader, fragmentShader);

    glAttribPosition = glGetAttribLocation(glProgId, "position");
    glUniformTexture = glGetUniformLocation(glProgId, "inputImageTexture");
    glAttribTextureCoordinate = glGetAttribLocation(glProgId, "inputTextureCoordinate");
    isInitialized = true;
}

void GPUImageFilter::onInitialized() {
    LOGI("%s", "GPUImageFilter onInitialized");
}

void GPUImageFilter::onDestory() {
    LOGI("%s", "GPUImageFilter onDestory");
}

void
GPUImageFilter::onDraw(int textureId, const void *cubeBufferPtr, const void *textureBufferPtr) {
    LOGE("%s", "GPUImageFilter onDraw.");
    LOGE("GPUImageFilter glProgId:%d", glProgId);
    glUseProgram(glProgId);
    runPendingOnDrawTasks();
    /*if (!isInitialized) {
        LOGE("%s", "isInitialized is false!");
        return;
    }*/
    //cubeBuffer.position(0);
    setGlAttribPosition(0);
    glVertexAttribPointer(glAttribPosition, 2, GL_FLOAT, false, 0, cubeBufferPtr);
    glEnableVertexAttribArray(glAttribPosition);
    //textureBuffer.position(0);
    setGlAttribPosition(0);
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

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    eglSwapBuffers(getEglDisplay(), getEglSurface());

    LOGE("%s", "GPUImageFilter-->onDraw complete！");
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
    LOGE("%s", "GPUImageFilter ifNeedInit");
    if (!isInitialized) {
        LOGE("%s", "GPUImageFilter call on init and initialized");
        this->onInit();
        this->onInitialized();
    }
}

/**
 * run draw thread callback.
 * @param arg
 * @return
 */
void *onRunDrawGlCallback(void *arg) {
    LOGE("%s", "onRunDrawGlCallback");
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

void GPUImageFilter::addDrawThread(GL_VARS *glVars) {
   /* pthread_t *pthread;
    //runOnDrawThreads.push_back(pthread);
    glVars->pthread = pthread;
    runOnDrawGLVars.push_back(glVars);
*/
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


void GPUImageFilter::setInteger(int location, int intValue) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->intValue = intValue;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_INTEGER;
    addDrawThread(glVars);
}


void GPUImageFilter::setFloat(int location, float floatValue) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->floatValue = floatValue;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_FLOAT;
    addDrawThread(glVars);
}

void GPUImageFilter::setFloatVec2(int location, float *arrayValuePtr) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->arrayValuePtr = arrayValuePtr;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_VEC2;
    addDrawThread(glVars);
}

void GPUImageFilter::setFloatVec3(int location, float *arrayValuePtr) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->arrayValuePtr = arrayValuePtr;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_VEC3;
    addDrawThread(glVars);
}

void GPUImageFilter::setFloatVec4(int location, float *arrayValuePtr) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->arrayValuePtr = arrayValuePtr;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_VEC4;
    addDrawThread(glVars);
}

void GPUImageFilter::setFloatArray(int location, float *arrayValuePtr, int arrayValueLength) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->arrayValuePtr = arrayValuePtr;
    glVars->arrayValueLength = arrayValueLength;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_FLOAT_ARRAY;
    addDrawThread(glVars);
}

void GPUImageFilter::setPoint(int location, float x, float y) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->x = x;
    glVars->y = y;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_POINT;
    addDrawThread(glVars);
}

void GPUImageFilter::setUniformMatrix3f(int location, float *arrayValuePtr) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->arrayValuePtr = arrayValuePtr;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX3F;
    addDrawThread(glVars);
}

void GPUImageFilter::setUniformMatrix4f(int location, float *arrayValuePtr) {
    GL_VARS *glVars = new GL_VARS();
    glVars->location = location;
    glVars->arrayValuePtr = arrayValuePtr;
    glVars->filter = this;
    glVars->glDrawType = GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX4F;
    addDrawThread(glVars);
}


void GPUImageFilter::runPendingOnDrawTasks() {
    /*if (this->runOnDrawGLVars.empty()) {
        return;
    }
    for (int i = 0; i < runOnDrawGLVars.size(); i++) {
        //create thread
        LOGE("run thread %d", i);
        pthread_create(runOnDrawGLVars[i]->pthread, NULL, onRunDrawGlCallback, runOnDrawGLVars[i]);
    }*/

}

ANativeWindow *GPUImageFilter::getNativeWindow() const {
    return nativeWindow;
}

void GPUImageFilter::setNativeWindow(ANativeWindow *nativeWindow) {
    GPUImageFilter::nativeWindow = nativeWindow;
}

EGLDisplay *GPUImageFilter::getEglDisplay() const {
    return eglDisplay;
}

void GPUImageFilter::setEglDisplay(EGLDisplay *eglDisplay) {
    GPUImageFilter::eglDisplay = eglDisplay;
}

EGLSurface *GPUImageFilter::getEglSurface() const {
    return eglSurface;
}

void GPUImageFilter::setEglSurface(EGLSurface *eglSurface) {
    GPUImageFilter::eglSurface = eglSurface;
}


