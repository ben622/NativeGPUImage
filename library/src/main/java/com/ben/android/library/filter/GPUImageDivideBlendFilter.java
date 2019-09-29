package com.ben.android.library.filter;

import android.graphics.Bitmap;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageDivideBlendFilter extends GPUImageTwoInputFilter {
    public GPUImageDivideBlendFilter() {
        this(null);
    }

    public GPUImageDivideBlendFilter(Bitmap bitmap) {
        super(FilterType.BLEND_DIVIDE.ordinal(), bitmap);
    }
}
