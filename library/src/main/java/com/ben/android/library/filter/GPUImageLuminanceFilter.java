package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/8
 */
public class GPUImageLuminanceFilter extends NativeFilter {
    public GPUImageLuminanceFilter() {
        super(FilterType.LUMINANCE.ordinal());
    }
}
