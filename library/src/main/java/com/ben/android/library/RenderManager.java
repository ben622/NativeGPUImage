package com.ben.android.library;

import android.graphics.Bitmap;
import android.os.Handler;
import android.os.Looper;
import android.widget.ImageView;

import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.load.engine.DataFetcherGenerator;
import com.ben.android.library.load.engine.DataGenerator;
import com.ben.android.library.load.engine.Resource;
import com.ben.android.library.load.fetcher.DataFetcher;
import com.ben.android.library.load.fetcher.FileFetcher;
import com.ben.android.library.load.fetcher.HttpUrlFetcher;
import com.ben.android.library.render.Render;
import com.ben.android.library.render.RenderFetcherGenerator;
import com.ben.android.library.render.RenderGenerator;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class RenderManager implements DataFetcherGenerator.FetcherReadyCallback {
    private NativeFilter mFilter;
    private LinkedBlockingQueue<DataFetcherGenerator> mFetcherQueue = new LinkedBlockingQueue<>();
    private LinkedBlockingQueue<Render> mRenderQueue;

    private Handler mHandler = new Handler(Looper.getMainLooper());

    public <T extends NativeFilter> RenderManager applyFilter(T filter){
        mFilter = filter;
        return this;
    }


    public RenderManager applyBitmaps(Bitmap... bitmaps) {
        mFetcherQueue.peek().start();
        return this;
    }

    public RenderManager applyBitmapByUrls(String... urls) {
        for (String url : urls) {
            mFetcherQueue.add(new DataGenerator(new HttpUrlFetcher(url), this));
        }
        return this;
    }

    public RenderManager applyBitmapByFiles(String ... files){
        for (String file : files) {
            mFetcherQueue.add(new DataGenerator(new FileFetcher(file), this));
        }
        return this;
    }

    public RenderManager applyBitmapByFiles(File ... files){
        for (File file : files) {
            mFetcherQueue.add(new DataGenerator(new FileFetcher(file), this));
        }
        return this;
    }


    public void get() {

    }

    public RenderManager into(ImageView view) {

        return this;
    }
    public RenderManager register(NGPListener... listeners) {

        return this;
    }


    @Override
    public void onDataFetcherReady(Resource resource) {
        mRenderQueue.add(new Render());
    }

    @Override
    public void onDataFetcherFailed(Exception e) {

    }
}
