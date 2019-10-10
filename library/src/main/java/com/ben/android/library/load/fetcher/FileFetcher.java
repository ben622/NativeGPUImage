package com.ben.android.library.load.fetcher;

import android.util.Log;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class FileFetcher implements DataFetcher<InputStream>{
    private static final String TAG = FileFetcher.class.getSimpleName();
    private File file;

    public FileFetcher(String url) {
        this(new File(url));
    }

    public FileFetcher(File file) {
        this.file = file;
    }

    @Override
    public void loadData(DataCallback<? super InputStream> callback) {
        try {
            callback.onDataReady(new FileInputStream(file));
        } catch (FileNotFoundException e) {
            if (Log.isLoggable(TAG, Log.DEBUG)) {
                Log.d(TAG, "file not found ["+file.getPath()+"]", e);
            }
            callback.onLoadFailed(e);
        }
    }

    @Override
    public InputStream loadData() {
        try {
           return new FileInputStream(file);
        } catch (FileNotFoundException e) {
            if (Log.isLoggable(TAG, Log.DEBUG)) {
                Log.d(TAG, "file not found ["+file.getPath()+"]", e);
            }
        }
        return null;
    }
}
