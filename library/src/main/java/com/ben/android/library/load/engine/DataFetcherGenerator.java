package com.ben.android.library.load.engine;

import android.graphics.Bitmap;
import android.support.annotation.Nullable;

import com.ben.android.library.load.fetcher.DataFetcher;

import javax.sql.DataSource;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public interface DataFetcherGenerator {

    interface FetcherReadyCallback {

        void onDataFetcherReady(Resource resource);

        void onDataFetcherFailed( Exception e);
    }

    void start();
}
