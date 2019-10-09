package com.ben.android.library.load.engine;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

import com.ben.android.library.NGPNativeBridge;
import com.ben.android.library.load.fetcher.DataFetcher;

import java.io.InputStream;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class DataGenerator implements DataFetcherGenerator,DataFetcher.DataCallback<InputStream> {
    private DataFetcherGenerator.FetcherReadyCallback fetcherReadyCallback;
    private DataFetcher<InputStream> fetcher;

    public DataGenerator(DataFetcher<InputStream> fetcher,DataFetcherGenerator.FetcherReadyCallback fetcherReadyCallback) {
        this.fetcherReadyCallback = fetcherReadyCallback;
        this.fetcher = fetcher;
    }

    @Override
    public void onDataReady(@Nullable InputStream data) {
        Bitmap bitmap = BitmapFactory.decodeStream(data);
        if (bitmap.getConfig() != Bitmap.Config.ARGB_8888) {
            Bitmap resizedBitmap = Bitmap.createBitmap(bitmap.getWidth(), bitmap.getHeight(),
                    Bitmap.Config.ARGB_8888);
            Canvas can = new Canvas(resizedBitmap);
            can.drawARGB(0x00, 0x00, 0x00, 0x00);
            can.drawBitmap(bitmap, 0, 0, null);

            // TODO: 2019/10/9 bitmap recycle
            bitmap.recycle();

            fetcherReadyCallback.onDataFetcherReady(Resource.obtain(resizedBitmap));
        }else{
            fetcherReadyCallback.onDataFetcherReady(Resource.obtain(bitmap));
        }
    }

    @Override
    public void onLoadFailed(@NonNull Exception e) {
        fetcherReadyCallback.onDataFetcherFailed(e);
    }


    @Override
    public void start() {
        fetcher.loadData(this);
    }
}
