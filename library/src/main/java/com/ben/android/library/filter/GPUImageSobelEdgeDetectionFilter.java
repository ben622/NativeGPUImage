package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageSobelEdgeDetectionFilter extends NativeFilter{
    private float size;

    public GPUImageSobelEdgeDetectionFilter() {
        this(1.0f);
    }

    public GPUImageSobelEdgeDetectionFilter(float size) {
        super(FilterType.SOBEL_EDGE_DETECTION.ordinal());
        this.size = size;
    }

    public float getSize() {
        return size;
    }

    public void setSize(float size) {
        this.size = size;
    }
}
