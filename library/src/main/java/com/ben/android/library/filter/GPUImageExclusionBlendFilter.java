package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/29
 */
public class GPUImageExclusionBlendFilter extends GPUImageTwoInputFilter {
    public GPUImageExclusionBlendFilter() {
        super(FilterType.BLEND_EXCLUSION.ordinal(),null);
    }

}
