package com.ben.android.library.load.engine;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.util.Log;

import com.ben.android.library.load.fetcher.DataFetcher;

import java.io.InputStream;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class ResourceGenerator implements ResourceFetcherGenerator<Resource>, DataFetcher.DataCallback<Object> {
    private ResourceFetcherGenerator.FetcherReadyCallback fetcherReadyCallback;
    private DataFetcher<InputStream> fetcher;

    public ResourceGenerator(DataFetcher<InputStream> fetcher, ResourceFetcherGenerator.FetcherReadyCallback fetcherReadyCallback) {
        this.fetcherReadyCallback = fetcherReadyCallback;
        this.fetcher = fetcher;
    }

    @Override
    public void onDataReady(@Nullable Object data) {
        Bitmap bitmap = transcode(data);
        fetcherReadyCallback.onDataFetcherReady(Resource.obtain(bitmap));
    }

    private Bitmap transcode(@Nullable Object data) {
        Bitmap bitmap = null;
        if (data instanceof InputStream) {
            bitmap = BitmapFactory.decodeStream((InputStream) data);
        }
        if (data instanceof byte[]) {
            byte[] bytes = (byte[]) data;
            bitmap = BitmapFactory.decodeByteArray(bytes, 0, bytes.length);
        }
        if (bitmap.getConfig() != Bitmap.Config.ARGB_8888) {
            Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                    Bitmap.Config.ARGB_8888);
            Canvas can = new Canvas(resizedBitmap);
            can.drawARGB(0x00, 0x00, 0x00, 0x00);
            can.drawBitmap(bitmap, 0, 0, null);

            bitmap.recycle();
            return resizedBitmap;
        } else {
            return bitmap;
        }
    }

    @Override
    public void onLoadFailed(@NonNull Exception e) {
        fetcherReadyCallback.onDataFetcherFailed(e);
    }

    @Override
    public void run() {
        fetcher.loadData(this);
    }

    @Override
    public Resource call(){
        return Resource.obtain(transcode(fetcher.loadData()));
    }
}
