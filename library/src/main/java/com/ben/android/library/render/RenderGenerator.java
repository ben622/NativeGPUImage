package com.ben.android.library.render;

import android.graphics.Bitmap;

import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.load.engine.DataGenerator;
import com.ben.android.library.load.engine.Resource;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class RenderGenerator implements RenderFetcherGenerator {
    private Resource resource;
    private DataGenerator dataGenerator;
    @Override
    public void applyBitmaps(Bitmap... bitmaps) {
    }

    @Override
    public void applyBitmapByUrls(String... urls) {

    }

    @Override
    public void applyBitmapByFiles(String... files) {

    }

    @Override
    public void applyBitmapByFiles(File... files) {

    }
}
