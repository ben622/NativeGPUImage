package com.ben.android.library.filter;

import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/26
 */
public class GPUImageWhiteBalanceFilter extends NativeFilter {
    private float temperature;
    private float tint;

    public GPUImageWhiteBalanceFilter() {
        this(5000.0f, 0.0f);
    }

    public GPUImageWhiteBalanceFilter(float temperature, float tint) {
        super(FilterType.WHITE_BALANCE.ordinal());
        this.temperature = temperature;
        this.tint = tint;
    }

    public float getTemperature() {
        return temperature;
    }

    public void setTemperature(float temperature) {
        this.temperature = temperature;
    }

    public float getTint() {
        return tint;
    }

    public void setTint(float tint) {
        this.tint = tint;
    }
}
