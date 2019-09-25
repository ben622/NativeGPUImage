package com.ben.android.library;

import android.graphics.Bitmap;

import com.ben.android.library.filter.NativeFilter;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/25
 *
 * Android与NGP所有的操作将通过该类里的接口进行交互
 */
public class NGPNativeBridge {
    /**
     * 设置一个新的filter给ngp，这将会清除之前的filter。
     * @param filter
     * @param <T>
     */
    public native static <T extends NativeFilter> void setFilter(T filter);

    /**
     * 渲染指定的bitmap
     * @param bitmap
     */
    public native static void setBitmap(Bitmap bitmap);
}
