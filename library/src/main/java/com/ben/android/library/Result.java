package com.ben.android.library;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.text.TextUtils;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class Result {
    @NonNull
    private String path;

    public Result( @NonNull String path) {
        this.path = path;
    }

    @Nullable
    public Bitmap getBitmap() {
        return TextUtils.isEmpty(path) ? null : BitmapFactory.decodeFile(path);
    }

    @NonNull
    public String getPath() {
        return path;
    }

    public static Result obtain(File file) {
        return new Result(file.getPath());
    }

}
