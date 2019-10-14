package com.ben.android.library;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;
import android.widget.ImageView;

import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.load.engine.ResourceFetcherGenerator;
import com.ben.android.library.load.engine.ResourceGenerator;
import com.ben.android.library.load.engine.Resource;
import com.ben.android.library.load.fetcher.DataFetcher;
import com.ben.android.library.render.Render;
import com.ben.android.library.render.RenderFetcherGenerator;
import com.ben.android.library.render.RenderGenerator;
import com.ben.android.library.util.FilterType;
import com.ben.android.library.util.NGPListenerTools;
import com.ben.android.library.util.Rotation;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class RenderManager implements ResourceFetcherGenerator.FetcherReadyCallback, RenderFetcherGenerator.RenderFetcherCallback {
    private static final String TAG = RenderManager.class.getSimpleName();
    private static final int RESPONSE_CODE = 0x00;
    private RenderBuilder builder;
    private ImageView targetView;
    private boolean intoTargetView;
    private List<Result> mResultList = new ArrayList<>();

    private Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch (msg.what) {
                case RESPONSE_CODE:
                    if (mResultList.size() <= 0 || targetView == null) return;
                    targetView.setImageBitmap(mResultList.get(0).getBitmap());
                    break;
            }
        }
    };
    private RenderGenerator renderGenerator;

    public RenderManager(RenderBuilder builder) {
        this.builder = builder;
    }

    /**
     * 渲染至imageView，如果有多个渲染对象则只渲染第一个。
     *
     * @param imageView
     */
    public void into(ImageView imageView) {
        this.targetView = imageView;
        async(true);
    }

    public List<Result> get() {
        return sync();
    }

    /**
     * 异步渲染
     */
    private void async(boolean isFirst) {
        intoTargetView = isFirst;
        renderGenerator = new RenderGenerator(builder, this);
        NGPExecutors.execute(renderGenerator);
        for (int i = 0; i < (isFirst ? (builder.getFetchers().isEmpty() ? 0 : 1) : builder.getFetchers().size()); i++) {
            DataFetcher fetcher = builder.getFetchers().get(i);
            NGPExecutors.execute(new ResourceGenerator(i,
                    fetcher, this));
        }
    }

    /**
     * 同步渲染
     *
     * @return
     */
    private List<Result> sync() {
        NGPListenerTools.callRenderStart(builder.getListener());
        NGPNativeBridge.nativeCreateGL();
        if (builder.getMultipleFilter().isEmpty()) {
            for (int i = 0; i < builder.getFetchers().size(); i++) {
                DataFetcher fetcher = builder.getFetchers().get(i);
                Resource resource = NGPExecutors.submit(new ResourceGenerator(i, fetcher, this));
                if (resource == null) {
                    Log.e(TAG, "resource  null!");
                    continue;
                }

                NativeFilter applyFilter = builder.getFilter();
                if (builder.getFilterListener() != null) {
                    Render.UpgradRender upgradRender = Render.UpgradRender.obtain(applyFilter);
                    upgradRender = builder.getFilterListener().apply(upgradRender, resource.getPosition());
                    applyFilter = upgradRender.getFilter();
                }

                int width = builder.getWidth() <= 0 ? resource.getBitmap().getWidth() : builder.getWidth();
                int height = builder.getHeight() <= 0 ? resource.getBitmap().getHeight() : builder.getHeight();
                NGPNativeBridge.nativeSurfaceChanged(width, height);
                NGPNativeBridge.nativeApplyFilter(applyFilter);
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
                        result = Result.obtain(applyFilter, FilterType.getFilterName(applyFilter), file);
                    } else {
                        result = Result.obtain(applyFilter, FilterType.getFilterName(applyFilter), resultBitmap);
                    }
                    mResultList.add(result);
                    NGPListenerTools.callRenderComplete(builder.getListener(),result);
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        } else {
            //一对多渲染
            for (NativeFilter nativeFilter : builder.getMultipleFilter()) {
                for (int i = 0; i < builder.getFetchers().size(); i++) {
                    DataFetcher fetcher = builder.getFetchers().get(i);
                    Resource resource = NGPExecutors.submit(new ResourceGenerator(i, fetcher, this));
                    if (resource == null) {
                        Log.e(TAG, "resource  null!");
                        continue;
                    }
                    NativeFilter applyFilter = nativeFilter;
                    int width = builder.getWidth() <= 0 ? resource.getBitmap().getWidth() : builder.getWidth();
                    int height = builder.getHeight() <= 0 ? resource.getBitmap().getHeight() : builder.getHeight();
                    NGPNativeBridge.nativeSurfaceChanged(width, height);
                    NGPNativeBridge.nativeApplyFilter(applyFilter);
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
                            result = Result.obtain(applyFilter, FilterType.getFilterName(applyFilter), file);
                        } else {
                            result = Result.obtain(applyFilter, FilterType.getFilterName(applyFilter), resultBitmap);
                        }
                        mResultList.add(result);
                        NGPListenerTools.callRenderComplete(builder.getListener(),result);
                    } catch (IOException e) {
                        e.printStackTrace();
                    }

                }
            }
        }
        NGPNativeBridge.nativeDestroyed();
        NGPListenerTools.callRenderFinish(builder.getListener());
        return mResultList;
    }

    @Override
    public void onDataFetcherReady(Resource resource) {
        renderGenerator.put(Render.obtain(resource, builder.getFilter()));
        if (intoTargetView) {
            renderGenerator.stop();
        } else if (resource.getPosition() == builder.getFetchers().size() - 1) {
            renderGenerator.stop();
        }

    }

    @Override
    public void onDataFetcherFailed(Exception e) {
        Log.e(TAG, "DataFetcherFailed: " + e.getMessage());
    }

    @Override
    public void onRenderReady(@Nullable Result result) {
        mResultList.add(result);
        if (intoTargetView) {
            mHandler.sendEmptyMessage(RESPONSE_CODE);
        }
    }

    @Override
    public void onRenderFailed(@NonNull Exception e) {
        Log.e(TAG, "RenderFailed: " + e.getMessage());
    }
}
