package com.ben.android.library;

import android.content.Context;
import android.graphics.Bitmap;
import android.widget.ImageView;

import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.load.fetcher.DataFetcher;
import com.ben.android.library.load.fetcher.FileFetcher;
import com.ben.android.library.load.fetcher.HttpUrlFetcher;

import java.io.File;
import java.util.ArrayList;
import java.util.List;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class RenderBuilder {
    private Context context;
    private boolean isGif;
    private NativeFilter filter;
    private ImageView targetView;
    private List<NGPListener> listeners;
    private List<DataFetcher> fetchers;
    //批处理过滤
    private NGPFilterListener filterListener;
    private int width;
    private int height;

    private boolean isAsync = true;

    public RenderBuilder(Context context) {
        this.context = context;
        listeners = new ArrayList<>();
        fetchers = new ArrayList<>();
    }

    public boolean isAsync() {
        return isAsync;
    }

    public Context getContext() {
        return context;
    }

    public boolean isGif() {
        return isGif;
    }

    public NativeFilter getFilter() {
        return filter;
    }

    public ImageView getTargetView() {
        return targetView;
    }

    public List<NGPListener> getListeners() {
        return listeners;
    }

    public List<DataFetcher> getFetchers() {
        return fetchers;
    }

    public NGPFilterListener getFilterListener() {
        return filterListener;
    }

    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    /**
     * 按照指定的宽度进行渲染
     * @param width
     * @return
     */
    public RenderBuilder applyWidth(int width) {
        this.width = width;
        return this;
    }

    /**
     * 按照指定的高度进行渲染
     * @param height
     * @return
     */
    public RenderBuilder applyHeight(int height) {
        this.height = height;
        return this;
    }

    public <T extends NativeFilter> RenderBuilder applyFilter(T filter){
        this.filter = filter;
        return this;
    }


    public RenderBuilder applyBitmaps(Bitmap... bitmaps) {

        return this;
    }

    public RenderBuilder applyBitmapByUrls(String... urls) {
        for (String url : urls) {
            fetchers.add(new HttpUrlFetcher(url));
        }
        return this;
    }

    public RenderBuilder applyBitmapByFiles(String ... files){
        for (String file : files) {
            fetchers.add(new FileFetcher(file));
        }
        return this;
    }

    public RenderBuilder applyBitmapByFiles(File... files){
        for (File file : files) {
            fetchers.add(new FileFetcher(file));
        }
        return this;
    }


    public RenderBuilder applyNGPFilter(NGPFilterListener filter){
        this.filterListener = filter;
        return this;
    }

    /**
     * 是否同步渲染，如果为同步则在当前线程堵塞渲染
     * @param isAsync true async else sync.
     * @return
     */
    public RenderBuilder isAsync(boolean isAsync) {
        this.isAsync = isAsync;
        return this;
    }

    public RenderBuilder asGif() {
        this.isGif = true;
        return this;
    }

    public RenderManager into(ImageView imageView) {
        this.targetView = imageView;
        RenderManager renderManager = new RenderManager(this);
        renderManager.begin();
        return renderManager;
    }
}
