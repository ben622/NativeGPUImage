package com.ben.android.library.render;


import android.graphics.Bitmap;

import com.ben.android.library.NGP;
import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.RenderBuilder;
import com.ben.android.library.Result;
import com.ben.android.library.load.engine.Resource;
import com.ben.android.library.util.FilterType;
import com.ben.android.library.util.NGPListenerTools;
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
    private RenderFetcherCallback callback;
    private LinkedBlockingQueue<Render> mRenderQueue = new LinkedBlockingQueue<>();
    private Object condition = new Object();
    private boolean isStop = false;

    public RenderGenerator(RenderBuilder builder, RenderFetcherCallback callback) {
        this.builder = builder;
        this.callback = callback;
    }

    @Override
    public void run() {
        synchronized (condition) {
            NGPListenerTools.callRenderStart(builder.getListener());
            NGPNativeBridge.nativeCreateGL();
            while (true) {
                if (isStop && mRenderQueue.size() <= 0) {
                    break;
                }
                Render render = mRenderQueue.poll();

                if (render == null) {
                    try {
                        condition.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
                if (render == null) continue;

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
                    Result result = null;
                    if (builder.isAutoFile()) {
                        File file = new File(NGP.get().getConfigure().getCacheDir(), System.currentTimeMillis() + ".jpg");
                        BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file));
                        resultBitmap.compress(Bitmap.CompressFormat.JPEG, 100, bos);
                        bos.flush();
                        bos.close();
                        resultBitmap.recycle();
                        if (callback != null) {
                            result = Result.obtain(render.getFilter(), FilterType.getFilterName(render.getFilter()), file);
                        }
                    } else {
                        if (callback != null) {
                            result = Result.obtain(render.getFilter(), FilterType.getFilterName(render.getFilter()), resultBitmap);
                        }
                    }
                    callback.onRenderReady(result);
                    NGPListenerTools.callRenderComplete(builder.getListener(),result);
                } catch (IOException e) {
                    if (callback != null) {
                        callback.onRenderFailed(e);
                    }
                }

            }
            NGPNativeBridge.nativeDestroyed();
            NGPListenerTools.callRenderFinish(builder.getListener());
        }
    }

    @Override
    public void put(Render render) {
        try {
            mRenderQueue.put(render);
            activ();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

    }

    @Override
    public void stop() {
        synchronized (condition) {
            isStop = true;
            condition.notify();
        }
    }

    @Override
    public void activ() {
        synchronized (condition) {
            condition.notify();
        }
    }
}
