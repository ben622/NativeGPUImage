package com.ben.android.library.filter;

import android.graphics.Bitmap;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageDissolveBlendFilter  extends GPUImageMixBlendFilter{
    public GPUImageDissolveBlendFilter() {
        this(1.0f);
    }

    public GPUImageDissolveBlendFilter(float mix) {
        this(null, mix);
    }

    public GPUImageDissolveBlendFilter(Bitmap bitmap) {
        this(bitmap, 1.0f);
    }


    public GPUImageDissolveBlendFilter(Bitmap bitmap, float alpha) {
        super(FilterType.BLEND_ALPHA.ordinal(), bitmap, alpha);
    }
}
