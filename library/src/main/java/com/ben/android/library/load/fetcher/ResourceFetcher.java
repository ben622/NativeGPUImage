package com.ben.android.library.load.fetcher;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;



/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class ResourceFetcher implements DataFetcher<Bitmap> {
    private Resources resource;
    private int resId;

    public ResourceFetcher(Resources resource, int resId) {
        this.resource = resource;
        this.resId = resId;
    }

    @Override
    public void loadData(DataCallback<? super Bitmap> callback) {
        try {
            callback.onDataReady(BitmapFactory.decodeResource(resource, resId));
        } catch (Exception e) {
            callback.onLoadFailed(e);
        }

    }

    @Override
    public Bitmap loadData() {
        return BitmapFactory.decodeResource(resource, resId);
    }
}
