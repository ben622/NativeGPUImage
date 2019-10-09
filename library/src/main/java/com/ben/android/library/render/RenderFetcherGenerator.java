package com.ben.android.library.render;

import android.graphics.Bitmap;

import com.ben.android.library.RenderManager;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public interface RenderFetcherGenerator {

    void applyBitmaps(Bitmap... bitmaps);

    void applyBitmapByUrls(String... urls);

    void applyBitmapByFiles(String... files);

    void applyBitmapByFiles(File... files);

}
