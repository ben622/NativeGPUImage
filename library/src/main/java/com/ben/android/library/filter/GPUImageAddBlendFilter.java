package com.ben.android.library.filter;

import android.graphics.Bitmap;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/28
 */
public class GPUImageAddBlendFilter extends GPUImageTwoInputFilter {
    public GPUImageAddBlendFilter() {
        this(FilterType.BLEND_ADD.ordinal(), null);
    }
    public GPUImageAddBlendFilter(Bitmap bitmap) {
        this(FilterType.BLEND_ADD.ordinal(), bitmap);
    }

    public GPUImageAddBlendFilter(int filterType, Bitmap bitmap) {
        super(filterType, bitmap);
    }
}
