package com.ben.android.library;

import android.graphics.Bitmap;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/21
 */
public interface NGPApi {
    Bitmap renderBitmapCapture(Bitmap src);

    byte[] renderYUV420(byte[] yuvd, int length);
}
