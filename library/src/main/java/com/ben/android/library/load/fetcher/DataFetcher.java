package com.ben.android.library.load.fetcher;

import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public interface DataFetcher<T> {
    interface DataCallback<T> {
        void onDataReady(@Nullable T data);
        void onLoadFailed(@NonNull Exception e);
    }
    void loadData(DataCallback<? super T> callback);
}
