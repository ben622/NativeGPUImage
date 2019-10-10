package com.ben.android.library;

import android.graphics.Bitmap;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class Result {
    @Nullable
    private Bitmap bitmap;
    @NonNull
    private String path;

    @Nullable
    public Bitmap getBitmap() {
        return bitmap;
    }

    public void setBitmap(@Nullable Bitmap bitmap) {
        this.bitmap = bitmap;
    }

    @NonNull
    public String getPath() {
        return path;
    }

    public void setPath(@NonNull String path) {
        this.path = path;
    }
}
