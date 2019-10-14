package com.ben.android.library.render;

import android.graphics.Bitmap;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import com.ben.android.library.Result;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public interface RenderFetcherGenerator extends Runnable {
    interface RenderFetcherCallback{
        void onRenderReady(@Nullable Result result);
        void onRenderFailed(@NonNull Exception e);
    }
    void put(Render render);

    void stop();

    void activ();
}
