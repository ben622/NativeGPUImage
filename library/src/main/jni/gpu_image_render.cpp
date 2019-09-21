//
// Created by ben622 on 2019/9/17.
//

#include "gpu_image_render.hpp"
#include "include/jni/JniHelpers.h"
#include <android/native_window_jni.h>
#include "util/jni_util.hpp"
#include "util/open_gl_util.hpp"

#include <math.h>

using namespace ben::util;

static EGLSurface winSurface;
static EGLDisplay display;
static ANativeWindow *nativeWindow;


static void onDrawFrame(ben::ngp::GPUImageRender *render) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    render->getFilter()->onDraw(render->getGlTextureId(), render->getGlCubeBuffer(),
                                render->getGlTextureBuffer());
}

static void nativeSurfaceCreated(JNIEnv *env, jobject javaThis, jobject surface, jobject jbitmap,
                                 jint imageWidth, jint imageHeight) {
    //1.准备opengl环境
    nativeWindow = ANativeWindow_fromSurface(env, surface);
    display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGE("%s", "get eglDisplay failed!");
        return;
    }
    if (EGL_TRUE != eglInitialize(display, NULL, NULL)) {
        LOGE("%s", "eglInitialize failed!");
        return;
    }
    //surface 配置
    //输出配置
    EGLConfig config;
    EGLint configNum;
    //输入配置
    EGLint configSpec[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_ALPHA_SIZE, 8,
            EGL_DEPTH_SIZE, 16,
            EGL_STENCIL_SIZE, 0,
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
            EGL_SURFACE_TYPE,
            EGL_WINDOW_BIT,
            EGL_NONE
    };

    if (EGL_TRUE != eglChooseConfig(display, configSpec, &config, 1, &configNum)) {
        LOGE("%s", "eglChooseConfig failed!");
        return;
    }
    //创建surface
    winSurface = eglCreateWindowSurface(display, config, nativeWindow, 0);

    if (winSurface == EGL_NO_SURFACE) {
        LOGE("%s", "eglCreateWindowSurface failed!");
        return;
    }
    //创建context
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
    };
    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, ctxAttr);
    if (context == EGL_NO_CONTEXT) {
        LOGE("%s", "eglCreateContext failed!");
        return;
    }
    //egl 关联 openl
    if (EGL_TRUE != eglMakeCurrent(display, winSurface, winSurface, context)) {
        LOGE("%s", "eglMakeCurrent failed!");
        return;
    }
    LOGI("%s", "egl init success!");

    //2.初始化GPUImageRender
    ben::ngp::GPUImageRender *render = getNativeClassPtr<ben::ngp::GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    if (!render) {
        LOGE("%s", "render is null");
        return;
    }

    //gl background
    glClearColor(render->getBackgroundRed(), render->getBackgroundGreen(),
                 render->getBackgroundBlue(), 1);
    glDisable(GL_DEPTH_TEST);

    //构造默认filter
    render->setIsPreparGLEnvironment(JNI_TRUE);

    ben::ngp::GPUImageFilter *filter = new ben::ngp::GPUImageFilter();
    filter->setNativeWindow(nativeWindow);
    filter->setEglDisplay(&display);
    filter->setEglSurface(&winSurface);
    render->setFilter(filter);
    //filter init
    render->getFilter()->ifNeedInit();

}

static void nativeSurfaceChanged(JNIEnv *env, jobject javaThis, jobject jbitmap, jint imageWidth,
                                 jint imageHeight, jint width, jint height) {
    LOGE("native surface changed::width[%d] height[%d]", width, height);
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env, jbitmap, &bitmapInfo) < 0) {
        return;
    }
    LOGI("showBitmap width %d, height %d, format %d", imageWidth, imageHeight,
         bitmapInfo.format);

    if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("%s", "invalid rgb format error!");
        return;
    }

    ben::ngp::GPUImageRender *render = getNativeClassPtr<ben::ngp::GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    if (!render->isIsPreparGLEnvironment()) {
        LOGE("%s", "opengl environment is not ready!");
        return;
    }
    //重新设置filter
    ben::ngp::GPUImageZoomBlurFilter *filter = new ben::ngp::GPUImageZoomBlurFilter();
    filter->setNativeWindow(nativeWindow);
    filter->setEglDisplay(&display);
    filter->setEglSurface(&winSurface);
    render->setFilter(filter);
    //filter init
    render->getFilter()->ifNeedInit();
    /*ben::ngp::GPUImageDilationFilter *pFilter = new ben::ngp::GPUImageDilationFilter();
    pFilter->setNativeWindow(nativeWindow);
    pFilter->setEglDisplay(&display);
    pFilter->setEglSurface(&winSurface);
    for (ben::ngp::GPUImageFilter *filter : pFilter->getFilters()) {
        filter->setNativeWindow(nativeWindow);
        filter->setEglDisplay(&display);
        filter->setEglSurface(&winSurface);
    }
    for (ben::ngp::GPUImageFilter *filter : pFilter->getMergedFilters()) {
        filter->setNativeWindow(nativeWindow);
        filter->setEglDisplay(&display);
        filter->setEglSurface(&winSurface);
    }
    render->setFilter(pFilter);
    render->getFilter()->ifNeedInit();
*/
    //create texureid
    render->setGlTextureId(
            loadTextureByBitmap(env, jbitmap, imageWidth, imageHeight, render->getGlTextureId()));
    LOGE("gl textureid %d", render->getGlTextureId());
    render->setImageWidth(imageWidth);
    render->setImageHeight(imageHeight);

    //reset width height。
    int windowWidth = width;
    int windowHeight = height;
    if (windowWidth > windowHeight) {
        windowHeight = width;
        windowWidth = height;
    }
    render->setOutputWidth(windowWidth);
    render->setOutputHeight(windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);
    glUseProgram(render->getFilter()->getGlProgId());
    render->getFilter()->onOutputSizeChanged(windowHeight, windowHeight);
    render->adjustImageScaling();

    //run
    onDrawFrame(render);

}


ben::ngp::GPUImageRender::GPUImageRender() : JavaClass() {

}

ben::ngp::GPUImageRender::GPUImageRender(ben::ngp::GPUImageFilter *filter) {
    this->filter = filter;
}

ben::ngp::GPUImageRender::GPUImageRender(JNIEnv *env) : JavaClass(env) {
    initialize(env);
}

ben::ngp::GPUImageRender::~GPUImageRender() {

}

void ben::ngp::GPUImageRender::initialize(JNIEnv *env) {
    setClass(env);
    glCubeBuffer = CUBE;
    glTextureBuffer = TEXTURE_NO_ROTATION;
    setRotation(Rotation::NORMAL, false, false);

    addNativeMethod("nativeSurfaceCreated", (void *) nativeSurfaceCreated, kTypeVoid,
                    "Landroid/view/Surface;",
                    "Landroid/graphics/Bitmap;",
                    kTypeInt, kTypeInt, NULL);
    addNativeMethod("nativeSurfaceChanged", (void *) nativeSurfaceChanged, kTypeVoid,
                    "Landroid/graphics/Bitmap;",
                    kTypeInt, kTypeInt,
                    kTypeInt, kTypeInt, NULL);
    registerNativeMethods(env);
}


void ben::ngp::GPUImageRender::mapFields() {

}

const char *ben::ngp::GPUImageRender::getCanonicalName() const {
    return GPU_IMAGE_RENDER_CLASS;
}


int ben::ngp::GPUImageRender::getOutputWidth() const {
    return outputWidth;
}

void ben::ngp::GPUImageRender::setOutputWidth(int outputWidth) {
    GPUImageRender::outputWidth = outputWidth;
}

int ben::ngp::GPUImageRender::getOutputHeight() const {
    return outputHeight;
}

void ben::ngp::GPUImageRender::setOutputHeight(int outputHeight) {
    GPUImageRender::outputHeight = outputHeight;
}

int ben::ngp::GPUImageRender::getImageWidth() const {
    return imageWidth;
}

void ben::ngp::GPUImageRender::setImageWidth(int imageWidth) {
    GPUImageRender::imageWidth = imageWidth;
}

int ben::ngp::GPUImageRender::getImageHeight() const {
    return imageHeight;
}

void ben::ngp::GPUImageRender::setImageHeight(int imageHeight) {
    GPUImageRender::imageHeight = imageHeight;
}

bool ben::ngp::GPUImageRender::isIsPreparGLEnvironment() const {
    return isPreparGLEnvironment;
}

void ben::ngp::GPUImageRender::setIsPreparGLEnvironment(bool isPreparGLEnvironment) {
    GPUImageRender::isPreparGLEnvironment = isPreparGLEnvironment;
}

int ben::ngp::GPUImageRender::getGlTextureId() const {
    return glTextureId;
}

void ben::ngp::GPUImageRender::setGlTextureId(int glTextureId) {
    GPUImageRender::glTextureId = glTextureId;
}


int *ben::ngp::GPUImageRender::getGlRgbBuffer() const {
    return glRgbBuffer;
}

void ben::ngp::GPUImageRender::setGlRgbBuffer(int *glRgbBuffer) {
    GPUImageRender::glRgbBuffer = glRgbBuffer;
}

float ben::ngp::GPUImageRender::getBackgroundRed() const {
    return backgroundRed;
}

void ben::ngp::GPUImageRender::setBackgroundRed(float backgroundRed) {
    GPUImageRender::backgroundRed = backgroundRed;
}

float ben::ngp::GPUImageRender::getBackgroundGreen() const {
    return backgroundGreen;
}

void ben::ngp::GPUImageRender::setBackgroundGreen(float backgroundGreen) {
    GPUImageRender::backgroundGreen = backgroundGreen;
}

float ben::ngp::GPUImageRender::getBackgroundBlue() const {
    return backgroundBlue;
}

void ben::ngp::GPUImageRender::setBackgroundBlue(float backgroundBlue) {
    GPUImageRender::backgroundBlue = backgroundBlue;
}

bool ben::ngp::GPUImageRender::isFlipHorizontal() const {
    return flipHorizontal;
}

void ben::ngp::GPUImageRender::setFlipHorizontal(bool flipHorizontal) {
    GPUImageRender::flipHorizontal = flipHorizontal;
}

bool ben::ngp::GPUImageRender::isFlipVertical() const {
    return flipVertical;
}

void ben::ngp::GPUImageRender::setFlipVertical(bool flipVertical) {
    GPUImageRender::flipVertical = flipVertical;
}

ScaleType ben::ngp::GPUImageRender::getScaleType() const {
    return scaleType;
}

void ben::ngp::GPUImageRender::setScaleType(ScaleType scaleType) {
    GPUImageRender::scaleType = scaleType;
}

void ben::ngp::GPUImageRender::adjustImageScaling() {
    float outputWidth = this->getOutputWidth();
    float outputHeight = this->getOutputHeight();
    if (rotation == Rotation::ROTATION_270 || rotation == Rotation::ROTATION_90) {
        outputWidth = this->getOutputHeight();
        outputHeight = this->getOutputWidth();
    }

    float ratio1 = outputWidth / imageWidth;
    float ratio2 = outputHeight / imageHeight;

    float ratioMax = max(ratio1, ratio2);
    int imageWidthNew = round(imageWidth * ratioMax);
    int imageHeightNew = round(imageHeight * ratioMax);

    float ratioWidth = imageWidthNew / outputWidth;
    float ratioHeight = imageHeightNew / outputHeight;

    float *cube = CUBE;
    float *textureCords = ben::util::getRotation(rotation, flipHorizontal, flipVertical);
    if (scaleType == ScaleType::CENTER_CROP) {
        float distHorizontal = (1 - 1 / ratioWidth) / 2;
        float distVertical = (1 - 1 / ratioHeight) / 2;
        textureCords = new float[8]{
                addDistance(textureCords[0], distHorizontal),
                addDistance(textureCords[1], distVertical),
                addDistance(textureCords[2], distHorizontal),
                addDistance(textureCords[3], distVertical),
                addDistance(textureCords[4], distHorizontal),
                addDistance(textureCords[5], distVertical),
                addDistance(textureCords[6], distHorizontal),
                addDistance(textureCords[7], distVertical),
        };
    } else {
        cube = new float[8]{
                CUBE[0] / ratioHeight, CUBE[1] / ratioWidth,
                CUBE[2] / ratioHeight, CUBE[3] / ratioWidth,
                CUBE[4] / ratioHeight, CUBE[5] / ratioWidth,
                CUBE[6] / ratioHeight, CUBE[7] / ratioWidth,
        };
    }

    this->glCubeBuffer = cube;
    this->glTextureBuffer = textureCords;
}

float ben::ngp::GPUImageRender::addDistance(float coordinate, float distance) {
    return coordinate == 0.0f ? distance : 1 - distance;

}

ben::ngp::GPUImageFilter *ben::ngp::GPUImageRender::getFilter() const {
    return filter;
}

void ben::ngp::GPUImageRender::setFilter(ben::ngp::GPUImageFilter *filter) {
    GPUImageRender::filter = filter;
}

float *ben::ngp::GPUImageRender::getGlCubeBuffer() const {
    return glCubeBuffer;
}

float *ben::ngp::GPUImageRender::getGlTextureBuffer() const {
    return glTextureBuffer;
}

Rotation ben::ngp::GPUImageRender::getRotation() const {
    return rotation;
}

void ben::ngp::GPUImageRender::setRotation(Rotation rotation) {
    GPUImageRender::rotation = rotation;
}

void
ben::ngp::GPUImageRender::setRotation(Rotation rotation, bool flipHorizontal, bool flipVertical) {
    this->flipHorizontal = flipHorizontal;
    this->flipVertical = flipVertical;
    setRotation(rotation);

}

