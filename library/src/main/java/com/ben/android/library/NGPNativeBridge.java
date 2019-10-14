package com.ben.android.library;

import android.graphics.Bitmap;
import android.view.Surface;

import com.ben.android.library.filter.NativeFilter;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/25

 * FBO离屏渲染CASE:
 * 1、NGPNativeBridge.init(); //只需执行一次
 * 2、NGPNativeBridge.nativeCreateGL();
 * 3、NGPNativeBridge.nativeSurfaceChanged(int width, int height);
 * 4、NGPNativeBridge.nativeApplyFilter(NativeFilter f);
 * 5、NGPNativeBridge.nativeApplyBitmap(Bitmap bitmap);
 *    NGPNativeBridge.nativeApplyYUV420(byte[] yuv);
 * 6、NGPNativeBridge.nativeCapture(Bitmap bitmap); //获取渲染后的Bitmap
 * 7、NGPNativeBridge.nativeDestroyed();
 *
 *
 * Surface渲染CASE:
 * 1、NGPNativeBridge.init(); //只需执行一次
 * 2、NGPNativeBridge.nativeSurfaceCreated(Surface surface);
 * 3、NGPNativeBridge.nativeSurfaceChanged(int width, int height);
 * 4、NGPNativeBridge.nativeApplyFilter(NativeFilter f);
 * 5、NGPNativeBridge.nativeApplyBitmap(Bitmap bitmap);
 *    NGPNativeBridge.nativeApplyYUV420(byte[] yuv);
 * 6、NGPNativeBridge.nativeRequestRender();
 * 7、NGPNativeBridge.nativeDestorySurfaceGL();
 */
public class NGPNativeBridge {
    public static void init() {
        System.loadLibrary("gpuimage");
    }

    /**
     * 设置一个filter到Native GL
     * @param filter 必须指定{@link NativeFilter#setFilterType(int)}
     * @param <T>
     */
    public native static <T extends NativeFilter> void nativeApplyFilter(T filter);

    /**
     * 渲染的Bitmap
     * @param bitmap
     */
    public native static void nativeApplyBitmap(Bitmap bitmap);

    /**
     * 渲染的YUV数据
     * @param yuv
     */
    public native static void nativeApplyYUV420(byte[] yuv,int width,int height);

    /**
     * 从Native GL中截取渲染结果，FBO离屏渲染或Surface渲染都可以调用该函数，注意调用该函数时会在Native中再次请求渲染,所以在Camera非FBO实时渲染过程中不建议频繁调用该函数。
     * @param bitmap
     */
    public native static void nativeCapture(Bitmap bitmap);
    /**
     * use this method request egl render.
     */
    public native static void nativeRequestRender();

    /**
     * 当需要将GL中的渲染效果直接展示出来的时候使用此函数创建GL环境
     * @param surface
     */
    public native static void nativeSurfaceCreated(Surface surface);

    /**
     * 设置Native中的outputWidth以及outputHeight，使用FBO离屏渲染或使用Surface渲染都需要调用此函数
     * @param width
     * @param height
     */
    public native static void nativeSurfaceChanged(int width, int height);

    /**
     * 销毁Native中的FBO GL环境，再次渲染需要重新使用{@link NGPNativeBridge#nativeCreateGL()}进行初始化
     */
    public native static void nativeDestroyed();

    /**
     * 销毁Native中的Surface GL环境，再次渲染需要重新使用{@link NGPNativeBridge#nativeSurfaceCreated(Surface)}进行初始化
     */
    public native static void nativeDestorySurfaceGL();

    /**
     * 在Native中创建支持FBO渲染的GL环境
     */
    public native static void nativeCreateGL();

    public native static void nativeApplyRotation(int rotation, boolean flipHorizontal, boolean flipVertical);

    public native static void nativeApplyScaleType(int scaleType);

}
