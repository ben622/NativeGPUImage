package com.ben.android.library.load.fetcher;

import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;



/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class ResourceFetcher implements DataFetcher<byte[]> {
    private Resources resource;
    private int resId;


    @Override
    public void loadData(DataCallback<? super byte[]> callback) {
        BitmapFactory.decodeResource(resource, resId);

    }

    @Override
    public byte[] loadData() {
        return new byte[0];
    }
}
