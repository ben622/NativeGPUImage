package com.ben.android.library;

import android.graphics.Bitmap;
import android.view.Surface;

import com.ben.android.library.filter.NativeFilter;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/25
 *
 * Android与NGP所有的操作将通过该类里的接口进行交互
 */
public class NGPNativeBridge {
    public static void init() {
        System.loadLibrary("gpuimage");
    }
    /**
     * set new filter to ngl.
     * @param filter
     * @param <T>
     */
    public native static <T extends NativeFilter> void setFilter(T filter);

    /**
     * render bitmap
     * @param bitmap
     */
    public native static void setBitmap(Bitmap bitmap);

    /**
     * 从gl中获取渲染后的bitmap
     * @param bitmap
     */
    public native static void capture(Bitmap bitmap);
    /**
     * use this method request egl render.
     */
    public native static void requestRender();

    public native static void nativeSurfaceCreated(Surface surface);

    public native static void nativeSurfaceChanged(int width, int height);

    public native static void nativeDestroyed();
    //FBO
    public native static void nativeCreateGL();
}
