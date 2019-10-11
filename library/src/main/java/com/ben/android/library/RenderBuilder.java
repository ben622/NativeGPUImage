package com.ben.android.library;

import android.content.Context;
import android.graphics.Bitmap;
import android.widget.ImageView;

import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.load.fetcher.DataFetcher;
import com.ben.android.library.load.fetcher.FileFetcher;
import com.ben.android.library.load.fetcher.HttpUrlFetcher;
import com.ben.android.library.util.Rotation;
import com.ben.android.library.util.ScaleType;

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
    private List<NGPListener> listeners;
    private List<DataFetcher> fetchers;
    //批处理过滤
    private NGPFilterListener filterListener;
    private int width;
    private int height;
    private Rotation rotation = Rotation.NORMAL;
    private ScaleType scaleType = ScaleType.CENTER_INSIDE;


    public RenderBuilder(Context context) {
        this.context = context;
        listeners = new ArrayList<>();
        fetchers = new ArrayList<>();
    }

    public Rotation getRotation() {
        return rotation;
    }

    public ScaleType getScaleType() {
        return scaleType;
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



    public RenderBuilder applyRotation(Rotation rotation) {
        this.rotation = rotation;
        return this;
    }

    public RenderBuilder applyScaleType(ScaleType scaleType) {
        this.scaleType = scaleType;
        return this;
    }

    public RenderBuilder asGif() {
        this.isGif = true;
        return this;
    }
    public RenderManager build(){
        return new RenderManager(this);
    }
}
