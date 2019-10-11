package com.ben.android.library.load.fetcher;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;


/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class MemoryFetcher implements DataFetcher<Bitmap> {
    private Bitmap bitmap;

    public MemoryFetcher(Bitmap bitmap) {
        this.bitmap = bitmap;
    }

    @Override
    public void loadData(DataCallback<? super Bitmap> callback) {
        try {
            callback.onDataReady(bitmap);
        } catch (Exception e) {
            callback.onLoadFailed(e);
        }

    }

    @Override
    public Bitmap loadData() {
        return bitmap;
    }
}
