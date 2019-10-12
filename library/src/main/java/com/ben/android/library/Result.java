package com.ben.android.library;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.text.TextUtils;

import com.ben.android.library.filter.NativeFilter;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public class Result {
    @NonNull
    private String path;
    private NativeFilter filter;
    private String filterName;
    public Result( NativeFilter filter, String filterName,@NonNull String path) {
        this.path = path;
        this.filter = filter;
        this.filterName = filterName;
    }

    @Nullable
    public Bitmap getBitmap() {
        return TextUtils.isEmpty(path) ? null : BitmapFactory.decodeFile(path);
    }

    @NonNull
    public String getPath() {
        return path;
    }

    public NativeFilter getFilter() {
        return filter;
    }

    public String getFilterName() {
        return filterName;
    }

    public static Result obtain(NativeFilter filter,String filterName,File file) {
        return new Result(filter,filterName,file.getPath());
    }

}
