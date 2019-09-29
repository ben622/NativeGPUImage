package com.ben.android.library.filter;

import android.graphics.Bitmap;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageAlphaBlendFilter extends GPUImageMixBlendFilter {
    public GPUImageAlphaBlendFilter() {
        this(1.0f);
    }

    public GPUImageAlphaBlendFilter(float mix) {
        this(null, mix);
    }

    public GPUImageAlphaBlendFilter(Bitmap bitmap) {
        this(bitmap, 1.0f);
    }


    public GPUImageAlphaBlendFilter(Bitmap bitmap, float alpha) {
        super(FilterType.BLEND_ALPHA.ordinal(), bitmap, alpha);
    }
}
