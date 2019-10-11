package com.ben.android.library.render;

import android.graphics.Bitmap;

import com.ben.android.library.RenderManager;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public interface RenderFetcherGenerator extends Runnable {
    void put(Render render);

    void stop();

    void activ();
}
