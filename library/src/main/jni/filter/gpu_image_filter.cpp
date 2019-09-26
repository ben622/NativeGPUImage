//
// Created by ben622 on 2019/9/16.
//
#include "gpu_image_filter.hpp"

using namespace ben::util;
using namespace ben::ngp;

//filter
GPUImageFilter::GPUImageFilter() {
    this->vertexShader = NO_FILTER_VERTEX_SHADER;
    this->fragmentShader = NO_FILTER_FRAGMENT_SHADER;
}

GPUImageFilter::GPUImageFilter(char *vertexShaderArg, char *fragmentShaderArg, JNIEnv *env)
        : JavaClass(env) {
    this->vertexShader = vertexShaderArg;
    this->fragmentShader = fragmentShaderArg;
}


GPUImageFilter::GPUImageFilter(char *vertexShaderArg, char *fragmentShaderArg) {
    this->vertexShader = vertexShaderArg;
    this->fragmentShader = fragmentShaderArg;
}


void GPUImageFilter::onInit() {
    glProgId = loadProgram(vertexShader, fragmentShader);

    glAttribPosition = glGetAttribLocation(glProgId, "position");
    glUniformTexture = glGetUniformLocation(glProgId, "inputImageTexture");
    glAttribTextureCoordinate = glGetAttribLocation(glProgId, "inputTextureCoordinate");
    isFilterInitialized = true;
}

void GPUImageFilter::onInitialized() {
    LOGI("%s", "GPUImageFilter onInitialized");
}

void GPUImageFilter::onDestory() {
    LOGI("%s", "GPUImageFilter onDestory");
}

void
GPUImageFilter::onDraw(int textureId, float *cubeBufferPtr, float *textureBufferPtr) {
    //activity
    glUseProgram(glProgId);
    runPendingOnDrawTasks();
    if (!isFilterInitialized) {
        LOGE("%s", "isFilterInitialized is false!");
        return;
    }

    glVertexAttribPointer(glAttribPosition, 2, GL_FLOAT, false, 0, cubeBufferPtr);
    glEnableVertexAttribArray(glAttribPosition);
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

    if (getEglDisplay() == NULL || getEglSurface() == NULL) {
        LOGI("%s", "EglDisplay or EglSurface is Null!");
        return;
    }
    if (isFBO) {
        LOGI("%s", "fbo render!");
        return;
    }
    eglSwapBuffers(*getEglDisplay(), *getEglSurface());
}

void GPUImageFilter::onOutputSizeChanged(int width, int height) {
    this->outputWidth = width;
    this->outputHeight = height;
}

void GPUImageFilter::destory() {
    isFilterInitialized = false;
    glDeleteProgram(glProgId);
    onDestory();
}

void GPUImageFilter::onDrawArraysPre() {

}

void GPUImageFilter::ifNeedInit() {
    if (!isFilterInitialized) {
        this->onInit();
        this->onInitialized();
    }
}

/**
 * run draw thread callback.
 * @param arg
 * @return
 */
static void *onRunDrawGlCallback(void *arg) {
    GL_VARS *glVars = static_cast<GL_VARS *>(arg);
    static_cast<GPUImageFilter *>(glVars->filter)->ifNeedInit();
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_INTEGER) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_INTEGER");
        glUniform1i(glVars->location, glVars->intValue);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_FLOAT");
        glUniform1f(glVars->location, glVars->floatValue);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_VEC2) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_FLOAT_VEC2");
        glUniform2fv(glVars->location, 1, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_VEC3) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_FLOAT_VEC3");
        glUniform3fv(glVars->location, 1, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_VEC4) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_FLOAT_VEC4");
        glUniform4fv(glVars->location, 1, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_FLOAT_ARRAY) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_FLOAT_ARRAY");
        glUniform1fv(glVars->location, glVars->arrayValueLength, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_POINT) {
        LOGI("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_POINT");
        static float vec2[] = {
                glVars->x,
                glVars->y
        };
        glUniform2fv(glVars->location, 1, vec2);
    }

    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX3F) {
        LOGE("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX3F");
        glUniformMatrix3fv(glVars->location, 1, false, glVars->arrayValuePtr);
    }
    if (glVars->glDrawType == GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX4F) {
        LOGE("gl thread type [%s]", "GL_DRAW_TYPE::DRAW_UNIFORM_MATRIX4F");
        glUniformMatrix4fv(glVars->location, 1, false, glVars->arrayValuePtr);
    }
    return 0;

}

void GPUImageFilter::addDrawThread(GL_VARS *glVars) {
    runOnDrawGLVars.push_back(glVars);
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
    if (this->runOnDrawGLVars.empty()) {
        return;
    }
    pthread_t *pt = (pthread_t *) malloc(runOnDrawGLVars.size() * sizeof(pthread_t));
    vector<GL_VARS *> temp = vector<GL_VARS *>(runOnDrawGLVars.size());
    for (int i = runOnDrawGLVars.size() - 1; i >= 0; i--) {
        temp[i] = runOnDrawGLVars[i];
    }
    for (int i = runOnDrawGLVars.size() - 1; i >= 0; i--) {
        pthread_create(&pt[i], NULL, onRunDrawGlCallback, temp[i]);
    }
    for (int i = runOnDrawGLVars.size() - 1; i >= 0; i--) {
        pthread_join(pt[i], NULL);
    }
    runOnDrawGLVars.clear();
    temp.clear();
    free(pt);

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

bool GPUImageFilter::isIsFilterInitialized() const {
    return isFilterInitialized;
}

void GPUImageFilter::setIsFilterInitialized(bool isFilterInitialized) {
    GPUImageFilter::isFilterInitialized = isFilterInitialized;
}

bool GPUImageFilter::isIsFBO() const {
    return isFBO;
}

void GPUImageFilter::setIsFBO(bool isFBO) {
    GPUImageFilter::isFBO = isFBO;
}

