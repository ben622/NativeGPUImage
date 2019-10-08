package com.ben.android.library.filter;

import android.support.annotation.FloatRange;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageHighlightShadowFilter extends NativeFilter {
    private  float shadows;
    private float highlights;

    public GPUImageHighlightShadowFilter() {
        this(0.0f, 1.0f);
    }

    public GPUImageHighlightShadowFilter(@FloatRange(from = 0.0f,to = 1.0f) float shadows, @FloatRange(from = 0.0f,to = 1.0f)float highlights) {
        super(FilterType.HIGHLIGHT_SHADOW.ordinal());
        this.shadows = shadows;
        this.highlights = highlights;
    }

    public float getShadows() {
        return shadows;
    }

    public void setShadows(float shadows) {
        this.shadows = shadows;
    }

    public float getHighlights() {
        return highlights;
    }

    public void setHighlights(float highlights) {
        this.highlights = highlights;
    }
}
