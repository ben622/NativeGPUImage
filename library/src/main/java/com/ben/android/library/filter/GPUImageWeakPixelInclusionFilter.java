package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/27
 */
public class GPUImageWeakPixelInclusionFilter extends  GPUImage3x3TextureSamplingFilter{

    public GPUImageWeakPixelInclusionFilter() {
        this(FilterType.WEAK_PIXEL_INCLUSION.ordinal());
    }

    public GPUImageWeakPixelInclusionFilter(int filterType) {
        super(filterType);
    }
}
