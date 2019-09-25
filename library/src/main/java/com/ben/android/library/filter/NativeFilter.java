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
    }

    public NativeFilter(int filterType) {
        this.filterType = filterType;
    }

    //如果要获取filter 应使用{@link NativeFilter#getNativeFilter(FilterType)}
    //private static HashMap<FilterType, NativeFilter> mCacheFilters = new HashMap<>();

    //public native static <T extends NativeFilter> T createNativeFilter(int filterType);
    /**
     * 该方法不应该被直接调用，应使用{@link NativeFilter#getNativeFilter(FilterType)}
     * @param nativeFilter
     * @param <T>
     * @return
     */
    /*public native static <T extends NativeFilter> T getNativeFilter(T nativeFilter);

    public static <T extends NativeFilter> T getNativeFilter(FilterType filterType) {
        if (mCacheFilters.containsKey(filterType)) {
            NativeFilter javaFilterObject = FilterTools.createJavaFilterObject(filterType);
            javaFilterObject.nPtr = mCacheFilters.get(filterType).nPtr;
            return (T) getNativeFilter(javaFilterObject);
        }else{
            T nfilter = createNativeFilter(filterType.ordinal());
            mCacheFilters.put(filterType, nfilter);
            return nfilter;
        }
    }*/

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
