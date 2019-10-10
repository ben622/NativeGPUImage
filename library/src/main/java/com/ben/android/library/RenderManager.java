package com.ben.android.library;

import android.graphics.Bitmap;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;

import com.ben.android.library.load.engine.ResourceFetcherGenerator;
import com.ben.android.library.load.engine.ResourceGenerator;
import com.ben.android.library.load.engine.Resource;
import com.ben.android.library.load.fetcher.DataFetcher;
import com.ben.android.library.render.Render;
import com.ben.android.library.render.RenderGenerator;

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
public class RenderManager implements ResourceFetcherGenerator.FetcherReadyCallback {
    private static final String TAG = RenderManager.class.getSimpleName();

    private RenderBuilder builder;
    private LinkedBlockingQueue<Render> mRenderQueue = new LinkedBlockingQueue<>();

    private List<Result> mResultList = new ArrayList<>();

    private Handler mHandler = new Handler(Looper.getMainLooper());

    public RenderManager(RenderBuilder builder) {
        this.builder = builder;
        initialize();
    }

    private void initialize() {
        NGPExecutors.execute(new RenderGenerator());
    }

    public void begin() {
        /**
         * 开启一个资源转换线程>从列表中循环处理>将处理后的数据放入到待渲染队列
         * 开启一个渲染线程> 从列表中循环渲染处理>将处理后的数据放入到渲染结果中
         *
         * 1、将需要渲染的资源转化成bitmap
         * 2、循环从待渲染的队列中获取bitmap进行渲染
         *
         * 3、将渲染后的bitmap保存至本地
         * 4、如果是单张图片渲染则直接将渲染后的bitmap渲染到targetView中
         * 5、如果是多张图片则返回这些图片的文件地址
         *
         */
        if (builder.isAsync()) {
            for (DataFetcher fetcher : builder.getFetchers()) {
                NGPExecutors.execute(new ResourceGenerator(fetcher, this));
            }
        } else {
            NGPNativeBridge.nativeCreateGL();
            long result = 0;
            int size = 0;
            for (DataFetcher fetcher : builder.getFetchers()) {
                Resource resource = NGPExecutors.submit(new ResourceGenerator(fetcher, this));
                if (resource == null) {
                    Log.e(TAG, "begin: resource is null!" );
                    continue;
                }
                long start = System.currentTimeMillis();
                int width = builder.getWidth() <= 0 ? resource.getBitmap().getWidth() : builder.getWidth();
                int height = builder.getHeight() <= 0 ? resource.getBitmap().getHeight() : builder.getHeight();
                NGPNativeBridge.nativeSurfaceChanged(width, height);
                NGPNativeBridge.nativeApplyFilter(builder.getFilter());
                NGPNativeBridge.nativeApplyBitmap(resource.getBitmap());
                Bitmap resultBitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
                NGPNativeBridge.nativeCapture(resultBitmap);
                long end = System.currentTimeMillis();
                result += (end - start);
                size++;

                try {
                    File file = new File(builder.getContext().getCacheDir(), System.currentTimeMillis()+".jpg");
                    BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file));
                    resultBitmap.compress(Bitmap.CompressFormat.JPEG, 100, bos);
                    bos.flush();
                    bos.close();
                    resultBitmap.recycle();

                } catch (IOException e) {
                    e.printStackTrace();
                }

                //builder.getTargetView().setImageBitmap(resultBitmap);
            }
            Log.e(TAG, "累计渲染图片数>" + size + "  累计耗时>" + result+"  平均单张图片渲染耗时>"+(result/size)+"毫秒");
            NGPNativeBridge.nativeDestroyed();
        }

    }


    @Override
    public void onDataFetcherReady(Resource resource) {
        try {
            mRenderQueue.put(Render.obtain(resource, builder.getFilter(), 0));
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onDataFetcherFailed(Exception e) {
        Log.e(TAG, "onDataFetcherFailed: " + e.getMessage());
    }
}
