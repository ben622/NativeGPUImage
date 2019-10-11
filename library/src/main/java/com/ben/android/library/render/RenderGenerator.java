package com.ben.android.library.render;


import android.graphics.Bitmap;

import com.ben.android.library.NGP;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.RenderBuilder;
import com.ben.android.library.load.engine.Resource;
import com.ben.android.library.util.Rotation;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class RenderGenerator implements RenderFetcherGenerator {
    private RenderBuilder builder;
    private LinkedBlockingQueue<Render> mRenderQueue = new LinkedBlockingQueue<>();
    private Object condition = new Object();
    private boolean isStop = false;

    public RenderGenerator(RenderBuilder builder) {
        this.builder = builder;
    }

    @Override
    public void run() {
        synchronized (condition) {
            NGPNativeBridge.nativeCreateGL();
            while (!isStop) {
                Render render = mRenderQueue.poll();

                if (render == null) {
                    try {
                        condition.wait();
                        render = mRenderQueue.poll();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }

                Resource resource = render.getResource();
                if (resource == null) {
                    continue;
                }

                if (builder.getFilterListener() != null) {
                    Render.UpgradRender upgradRender = Render.UpgradRender.obtain(render);
                    upgradRender = builder.getFilterListener().apply(upgradRender, render.getResource().getPosition());
                    render.setFilter(upgradRender.getFilter());
                }

                int width = resource.getBitmap().getWidth() <= 0 ? resource.getBitmap().getWidth() : resource.getBitmap().getWidth();
                int height = resource.getBitmap().getHeight() <= 0 ? resource.getBitmap().getHeight() : resource.getBitmap().getHeight();

                NGPNativeBridge.nativeSurfaceChanged(width, height);
                NGPNativeBridge.nativeApplyFilter(render.getFilter());
                NGPNativeBridge.nativeApplyRotation(Rotation.getValue(builder.getRotation()), false, false);
                NGPNativeBridge.nativeApplyScaleType(builder.getScaleType().ordinal());
                NGPNativeBridge.nativeApplyBitmap(resource.getBitmap());
                Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
                NGPNativeBridge.nativeCapture(resultBitmap);

                try {
                    File file = new File(NGP.get().getConfigure().getCacheDir(), System.currentTimeMillis() + ".jpg");
                    BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file));
                    resultBitmap.compress(Bitmap.CompressFormat.JPEG, 100, bos);
                    bos.flush();
                    bos.close();
                    resultBitmap.recycle();

                } catch (IOException e) {
                    e.printStackTrace();
                }

            }

            NGPNativeBridge.nativeDestroyed();
        }
    }

    @Override
    public void put(Render render) {
        try {
            mRenderQueue.put(render);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    @Override
    public void stop() {
        isStop = true;

    }

    @Override
    public void activ() {
        synchronized (condition) {
            condition.notify();
        }
    }
}
