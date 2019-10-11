//
// Created by ben622 on 2019/9/25.
//

#include "android_gl_bridge.hpp"
#include "../util/jni_util.hpp"
#include "../util/filter_type.hpp"
#include "../gpu_image_render.hpp"

using namespace ben::util;

ben::ngp::NGPNativeBridge::NGPNativeBridge(JNIEnv *env) : JavaClass(env) {
    initialize(env);
}

void ben::ngp::NGPNativeBridge::initialize(JNIEnv *env) {
    setClass(env);
    addNativeMethod("nativeApplyFilter", (void *) &nativeApplyFilter,
                    kTypeVoid,
                    "Lcom/ben/android/library/filter/NativeFilter;", NULL);

    addNativeMethod("nativeApplyBitmap", (void *) &nativeApplyBitmap,
                    kTypeVoid,
                    "Landroid/graphics/Bitmap;", NULL);

    addNativeMethod("nativeCapture", (void *) &nativeCapture,
                    kTypeVoid,
                    "Landroid/graphics/Bitmap;", NULL);

    addNativeMethod("nativeRequestRender", (void *) &nativeRequestRender,
                    kTypeVoid, NULL);

    addNativeMethod("nativeSurfaceCreated", (void *) nativeSurfaceCreated, kTypeVoid,
                    "Landroid/view/Surface;", NULL);

    addNativeMethod("nativeSurfaceChanged", (void *) nativeSurfaceChanged, kTypeVoid,
                    kTypeInt, kTypeInt, NULL);

    addNativeMethod("nativeDestroyed", (void *) nativeDestroyed, kTypeVoid, NULL);

    addNativeMethod("nativeDestorySurfaceGL", (void *) nativeDestorySurfaceGL, kTypeVoid, NULL);

    addNativeMethod("nativeCreateGL", (void *) nativeCreateGL, kTypeVoid, NULL);

    addNativeMethod("nativeApplyRotation", (void *) nativeApplyRotation, kTypeVoid, kTypeInt,
                    kTypeBool, kTypeBool, NULL);

    addNativeMethod("nativeApplyScaleType", (void *) nativeApplyScaleType, kTypeVoid, kTypeInt,
                    NULL);

    registerNativeMethods(env);
}

void ben::ngp::NGPNativeBridge::mapFields() {

}

const char *ben::ngp::NGPNativeBridge::getCanonicalName() const {
    return "com/ben/android/library/NGPNativeBridge";
}

void
ben::ngp::NGPNativeBridge::nativeSurfaceCreated(JNIEnv *env, jclass javaThis, jobject surface) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->nativeSurfaceCreated(env, javaThis,
                                                                                    surface);
}

void ben::ngp::NGPNativeBridge::nativeSurfaceChanged(JNIEnv *env, jclass javaThis, jint width,
                                                     jint height) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->nativeSurfaceChanged(env, javaThis,
                                                                                    width, height);

}

void ben::ngp::NGPNativeBridge::nativeDestroyed(JNIEnv *env, jclass javaThis) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->nativeDestroyed(env, javaThis);
}

void ben::ngp::NGPNativeBridge::nativeDestorySurfaceGL(JNIEnv *env, jclass javaThis) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->nativeDestorySurfaceGL(env,
                                                                                      javaThis);

}

void ben::ngp::NGPNativeBridge::nativeCreateGL(JNIEnv *env, jclass javaThis) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->nativeCreateGL(env, javaThis);

}

void ben::ngp::NGPNativeBridge::nativeCapture(JNIEnv *env, jclass javaThis, jobject object) {
    GPUImageRender *render = getNativeClassPtr<GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    render->getFilter()->setIsFBO(true);
    if (dynamic_cast<GPUImageFilterGroup *>(render->getFilter()) != NULL) {
        GPUImageFilterGroup *filterGroup = dynamic_cast<GPUImageFilterGroup *>(render->getFilter());
        for (ben::ngp::GPUImageFilter *filter : filterGroup->getFilters()) {
            filter->setIsFBO(true);
        }
        for (ben::ngp::GPUImageFilter *filter : filterGroup->getMergedFilters()) {
            filter->setIsFBO(true);
        }
    }
    render->reqeustRender();
    unsigned char *srcByteBuffer;
    int result = 0;
    int i, j;
    AndroidBitmapInfo srcInfo;

    result = AndroidBitmap_getInfo(env, object, &srcInfo);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        return;
    }

    result = AndroidBitmap_lockPixels(env, object, (void **) &srcByteBuffer);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        return;
    }

    int width = srcInfo.width;
    int height = srcInfo.height;
    glReadPixels(0, 0, srcInfo.width, srcInfo.height, GL_RGBA, GL_UNSIGNED_BYTE,
                 srcByteBuffer);

    int *pIntBuffer = (int *) srcByteBuffer;

    for (i = 0; i < height / 2; i++) {
        for (j = 0; j < width; j++) {
            int temp = pIntBuffer[(height - i - 1) * width + j];
            pIntBuffer[(height - i - 1) * width + j] = pIntBuffer[i * width + j];
            pIntBuffer[i * width + j] = temp;
        }
    }
    AndroidBitmap_unlockPixels(env, object);
    LOGI("%s", "read pixels successful!");

    render->getFilter()->setIsFBO(false);
    if (dynamic_cast<GPUImageFilterGroup *>(render->getFilter()) != NULL) {
        GPUImageFilterGroup *filterGroup = dynamic_cast<GPUImageFilterGroup *>(render->getFilter());
        for (ben::ngp::GPUImageFilter *filter : filterGroup->getFilters()) {
            filter->setIsFBO(false);
        }
        for (ben::ngp::GPUImageFilter *filter : filterGroup->getMergedFilters()) {
            filter->setIsFBO(false);
        }
    }
}


void ben::ngp::NGPNativeBridge::nativeRequestRender(JNIEnv *env, jclass javaThis) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->reqeustRender();
}

void ben::ngp::NGPNativeBridge::nativeApplyBitmap(JNIEnv *env, jclass javaThis, jobject object) {
    GPUImageRender *render = getNativeClassPtr<GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    render->renderBitmap(env, object);
}

void ben::ngp::NGPNativeBridge::nativeApplyRotation(JNIEnv *env, jclass javaThis, jint rotation,
                                                    jboolean flipHorizontal,
                                                    jboolean flipVertical) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->setRotation(fromInt(rotation),
                                                                           flipHorizontal,
                                                                           flipVertical);
}

void ben::ngp::NGPNativeBridge::nativeApplyScaleType(JNIEnv *env, jclass javaThis, jint scaleType) {
    getNativeClassPtr<GPUImageRender>(GPU_IMAGE_RENDER_CLASS)->setScaleType(
            fromScaleValue(scaleType));
}

void ben::ngp::NGPNativeBridge::nativeApplyFilter(JNIEnv *env, jclass javaThis, jobject object) {
    //convert java object to native object.
    NativeFilter *nativeFilterPtr = getNativeClassPtr<NativeFilter>(JAVA_NATIVE_FILTER);
    LOGI("native filter type:%d", nativeFilterPtr->getFilterType());
    nativeFilterPtr->setJavaObject(env, object);
    LOGI("java filter type:%d", nativeFilterPtr->getFilterType());
    GPUImageRender *render = getNativeClassPtr<GPUImageRender>(
            GPU_IMAGE_RENDER_CLASS);
    render->getFilter()->destory();

    GPUImageFilter *filterPtr = NULL;
    switch (nativeFilterPtr->getFilterType()) {
        case CONTRAST: {
            filterPtr = getNativeClassPtr<GPUImageContrastFilter>(JAVA_CONTRAST_FILTER);
            break;
        }
        case GRAYSCALE: {
            filterPtr = getNativeClassPtr<GPUImageGrayscaleFilter>(JAVA_GRAYSCALE_FILTER);
            break;
        }
        case SHARPEN: {
            filterPtr = getNativeClassPtr<GPUImageSharpenFilter>(JAVA_SHARPEN_FILTER);
            break;
        }
        case SEPIA: {
            break;
        }
        case SOBEL_EDGE_DETECTION: {
            GPUImageSobelEdgeDetectionFilter *filterPtr = getNativeClassPtr<GPUImageSobelEdgeDetectionFilter>(
                    JAVA_SOBEL_EDGE_DETECTION_FILTER);
            filterPtr->setJavaObject(env, object);
            render->resetFilter(filterPtr);
            filterPtr->setSize(filterPtr->getSize());
            break;
        }
        case THRESHOLD_EDGE_DETECTION: {
            GPUImageThresholdEdgeDetectionFilter *filterPtr = getNativeClassPtr<GPUImageThresholdEdgeDetectionFilter>(
                    JAVA_THRESHOLD_EDGE_DETECTION_FILTER);
            filterPtr->setJavaObject(env, object);
            render->resetFilter(filterPtr);
            filterPtr->setSize(filterPtr->getSize());
            filterPtr->setThreshold(filterPtr->getThreshold());
            break;
        }
        case SOBEL_THRESHOLD: {
            filterPtr = getNativeClassPtr<GPUImageSobelThresholdFilter>(
                    JAVA_SOBEL_THRESHOLD_FILTER);
            break;
        }
        case THREE_X_THREE_CONVOLUTION: {
            filterPtr = getNativeClassPtr<GPUImage3x3ConvolutionFilter>(
                    JAVA_3X3_CONVOLUTION_FILTER);
            break;
        }
        case FILTER_GROUP: {
            break;
        }
        case EMBOSS: {
            filterPtr = getNativeClassPtr<GPUImageEmbossFilter>(JAVA_EMBOSS_FILTER);
            break;
        }
        case POSTERIZE: {
            break;
        }
        case GAMMA: {
            filterPtr = getNativeClassPtr<GPUImageGammaFilter>(JAVA_GAMMA_FILTER);
            break;
        }
        case BRIGHTNESS: {
            filterPtr = getNativeClassPtr<GPUImageBrightnessFilter>(JAVA_BRIGHTNESS_FILTER);
            break;
        }
        case INVERT: {
            break;
        }
        case HUE: {
            filterPtr = getNativeClassPtr<GPUImageHueFilter>(JAVA_HUE_FILTER);
            break;
        }
        case PIXELATION: {
            filterPtr = getNativeClassPtr<GPUImagePixelationFilter>(JAVA_PIXELATION_FILTER);
            break;
        }
        case SATURATION: {
            filterPtr = getNativeClassPtr<GPUImageSaturationFilter>(JAVA_SATURATION_FILTER);
            break;
        }
        case EXPOSURE: {
            filterPtr = getNativeClassPtr<GPUImageExposureFilter>(JAVA_EXPOSURE_FILTER);
            break;
        }
        case HIGHLIGHT_SHADOW: {
            filterPtr = getNativeClassPtr<GPUImageHighlightShadowFilter>(
                    JAVA_HIGHLIGHT_SHADOW_FILTER);
            break;
        }
        case MONOCHROME: {
            filterPtr = getNativeClassPtr<GPUImageMonochromeFilter>(JAVA_MONOCHROME_FILTER);
            break;
        }
        case OPACITY: {
            break;
        }
        case RGB: {
            filterPtr = getNativeClassPtr<GPUImageRGBFilter>(JAVA_RGB_FILTER);
            break;
        }
        case WHITE_BALANCE: {
            filterPtr = getNativeClassPtr<GPUImageWhiteBalanceFilter>(JAVA_WHITE_BALANCE_FILTER);
            break;
        }
        case VIGNETTE: {
            GPUImageVignetteFilter *filterPtr = getNativeClassPtr<GPUImageVignetteFilter>(
                    JAVA_VIGNETTE_FILTER);
            filterPtr->setJavaObject(env, object);
            filterPtr->setVignetteColor(new float[3]{0.0f, 0.0f, 0.0f});
            render->resetFilter(filterPtr);
            break;
        }
        case TONE_CURVE: {
            break;
        }
        case LUMINANCE: {
            filterPtr = getNativeClassPtr<GPUImageLuminanceFilter>(JAVA_LUMINANCE_FILTER);
            break;
        }
        case LUMINANCE_THRESHSOLD: {
            filterPtr = getNativeClassPtr<GPUImageLuminanceThresholdFilter>(
                    JAVA_LUMINANCE_THRESHOLD_FILTER);
            break;
        }
        case BLEND_COLOR_BURN: {
            break;
        }
        case BLEND_COLOR_DODGE: {
            break;
        }
        case BLEND_DARKEN: {
            break;
        }
        case BLEND_DIFFERENCE: {
            break;
        }
        case BLEND_DISSOLVE: {
            GPUImageDissolveBlendFilter *filterPtr = getNativeClassPtr<GPUImageDissolveBlendFilter>(
                    JAVA_DISSOLVE_BLEND_FILTER);
            filterPtr->setJavaObject(env, object);
            readBitmapPixel(env, filterPtr);
            render->resetFilter(filterPtr);
            break;
        }
        case BLEND_EXCLUSION: {
            GPUImageExclusionBlendFilter *filterPtr = getNativeClassPtr<GPUImageExclusionBlendFilter>(
                    JAVA_EXCLUSION_BLEND_FILTER);
            filterPtr->setJavaObject(env, object);
            readBitmapPixel(env, filterPtr);
            render->resetFilter(filterPtr);
            break;
        }
        case BLEND_SOURCE_OVER: {
            break;
        }
        case BLEND_HARD_LIGHT: {
            break;
        }
        case BLEND_LIGHTEN: {
            break;
        }
        case BLEND_ADD: {
            GPUImageAddBlendFilter *filterPtr = getNativeClassPtr<GPUImageAddBlendFilter>(
                    JAVA_ADD_BLEND_FILTER);
            filterPtr->setJavaObject(env, object);
            readBitmapPixel(env, filterPtr);
            render->resetFilter(filterPtr);
            break;
        }
        case BLEND_DIVIDE: {
            GPUImageDivideBlendFilter *filterPtr = getNativeClassPtr<GPUImageDivideBlendFilter>(
                    JAVA_DIVIDE_BLEND_FILTER);
            filterPtr->setJavaObject(env, object);
            readBitmapPixel(env, filterPtr);
            render->resetFilter(filterPtr);
            break;
        }
        case BLEND_MULTIPLY: {
            break;
        }
        case BLEND_OVERLAY: {
            break;
        }
        case BLEND_SCREEN: {
            break;
        }
        case BLEND_ALPHA: {
            GPUImageAlphaBlendFilter *filterPtr = getNativeClassPtr<GPUImageAlphaBlendFilter>(
                    JAVA_ALPHA_BLEND_FILTER);
            filterPtr->setJavaObject(env, object);
            readBitmapPixel(env, filterPtr);
            render->resetFilter(filterPtr);
            break;
        }
        case BLEND_COLOR: {
            break;
        }
        case BLEND_HUE: {
            break;
        }
        case BLEND_SATURATION: {
            break;
        }
        case BLEND_LUMINOSITY: {
            break;
        }
        case BLEND_LINEAR_BURN: {
            break;
        }
        case BLEND_SOFT_LIGHT: {
            break;
        }
        case BLEND_SUBTRACT: {
            break;
        }
        case BLEND_CHROMA_KEY: {
            break;
        }
        case BLEND_NORMAL: {
            break;
        }
        case LOOKUP_AMATORKA: {
            break;
        }
        case GAUSSIAN_BLUR: {
            filterPtr = getNativeClassPtr<GPUImageGaussianBlurFilter>(JAVA_GAUSSIAN_BLUR_FILTER);
            break;
        }
        case CROSSHATCH: {
            filterPtr = getNativeClassPtr<GPUImageCrosshatchFilter>(JAVA_CROSSHATCH_FILTER);
            break;
        }
        case BOX_BLUR: {
            break;
        }
        case CGA_COLORSPACE: {
            break;
        }
        case DILATION: {
            filterPtr = getNativeClassPtr<GPUImageDilationFilter>(JAVA_DILATION_FILTER);
            break;
        }
        case KUWAHARA: {
            break;
        }
        case RGB_DILATION: {
            GPUImageRGBDilationFilter *filterPtr = getNativeClassPtr<GPUImageRGBDilationFilter>(
                    JAVA_RGB_DILATION_FILTER);
            filterPtr->setJavaObject(env, object);
            filterPtr->switchShader();
            render->resetFilter(filterPtr);
            break;
        }
        case SKETCH: {
            filterPtr = getNativeClassPtr<GPUImageSketchFilter>(JAVA_SKETCH_FILTER);
            break;
        }
        case TOON: {
            filterPtr = getNativeClassPtr<GPUImageToonFilter>(JAVA_TOON_FILTER);
            break;
        }
        case SMOOTH_TOON: {
            break;
        }
        case BULGE_DISTORTION: {
            break;
        }
        case GLASS_SPHERE: {
            break;
        }
        case HAZE: {
            filterPtr = getNativeClassPtr<GPUImageHazeFilter>(JAVA_HAZE_FILTER);
            break;
        }
        case LAPLACIAN: {
            break;
        }
        case NON_MAXIMUM_SUPPRESSION: {
            break;
        }
        case SPHERE_REFRACTION: {
            break;
        }
        case SWIRL: {
            break;
        }
        case WEAK_PIXEL_INCLUSION: {
            filterPtr = getNativeClassPtr<GPUImageWeakPixelInclusionFilter>(
                    JAVA_WEAK_PIXEL_INCLUSION_FILTER);
            break;
        }
        case FALSE_COLOR: {
            filterPtr = getNativeClassPtr<GPUImageFalseColorFilter>(JAVA_FALSE_COLOR_FILTER);
            break;
        }
        case COLOR_BALANCE: {
            break;
        }
        case LEVELS_FILTER_MIN: {
            filterPtr = getNativeClassPtr<GPUImageLevelsFilter>(JAVA_LEVELS_FILTER);
            break;
        }
        case BILATERAL_BLUR: {
            break;
        }
        case ZOOM_BLUR: {
            filterPtr = getNativeClassPtr<GPUImageZoomBlurFilter>(JAVA_ZOOM_BLUR_FILTER);
            break;
        }
        case HALFTONE: {
            filterPtr = getNativeClassPtr<GPUImageHalftoneFilter>(JAVA_HALFTONE_FILTER);
            break;
        }
        case TRANSFORM2D: {
            break;
        }
        case SOLARIZE: {
            filterPtr = getNativeClassPtr<GPUImageSolarizeFilter>(JAVA_SOLARIZE_FILTER);
            break;
        }
        case VIBRANCE: {
            filterPtr = getNativeClassPtr<GPUImageVibranceFilter>(JAVA_VIBRANCE_FILTER);
            break;
        }
        default: {
            LOGE("filter of type %d is not supported!", nativeFilterPtr->getFilterType());
            break;
        }
    }
    if (filterPtr != NULL) {
        filterPtr->setJavaObject(env, object);
        render->resetFilter(filterPtr);
    }

}

void
ben::ngp::NGPNativeBridge::readBitmapPixel(JNIEnv *env, ben::ngp::GPUImageTwoInputFilter *filter) {
    AndroidBitmapInfo bitmapInfo;
    if (AndroidBitmap_getInfo(env,
                              const_cast<jobject>(filter->getBitmap()),
                              &bitmapInfo) < 0) {
        return;
    }
    int bitmapWidth = bitmapInfo.width;
    int bitmapHeight = bitmapInfo.height;
    LOGI("image width %d, height %d, format %d", bitmapWidth, bitmapHeight,
         bitmapInfo.format);
    if (bitmapInfo.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGE("%s", "invalid rgb format error!");
        return;
    }
    void *pixel_source = NULL;
    AndroidBitmap_lockPixels(env, const_cast<jobject>(filter->getBitmap()), &pixel_source);
    filter->setPxiel(pixel_source);
    AndroidBitmap_unlockPixels(env, const_cast<jobject>(filter->getBitmap()));
    filter->setBitmapWidth(bitmapWidth);
    filter->setBitmapHeight(bitmapHeight);

}
