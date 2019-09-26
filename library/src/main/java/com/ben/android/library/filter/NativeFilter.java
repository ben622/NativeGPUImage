package com.ben.android.library.filter;

import com.ben.android.library.jni.NativeObject;
import com.ben.android.library.jni.annotations.UsedByNativeCode;
import com.ben.android.library.util.FilterTools;
import com.ben.android.library.util.FilterType;

import java.util.HashMap;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/24
 */
public class NativeFilter extends NativeObject {
    protected int filterType;

    public NativeFilter() {
        this(-1);
    }
    public NativeFilter(int filterType) {
        this.filterType = filterType;
    }

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public int getFilterType() {
        return filterType;
    }

    @SuppressWarnings("UnusedDeclaration")
    @UsedByNativeCode
    public void setFilterType(int filterType) {
        this.filterType = filterType;
    }

    @Override
    public void destroy() {

    }
}
