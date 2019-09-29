package com.ben.android.library.filter;

import android.graphics.Bitmap;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageMixBlendFilter  extends GPUImageTwoInputFilter{
    private float mix;

    public GPUImageMixBlendFilter(float mix) {
        this.mix = mix;
    }

    public GPUImageMixBlendFilter(int filterType, Bitmap bitmap, float mix) {
        super(filterType, bitmap);
        this.mix = mix;
    }

    public float getMix() {
        return mix;
    }

    public void setMix(float mix) {
        this.mix = mix;
    }
}
