package com.ben.android.library.filter;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import com.ben.android.library.R;
import com.ben.android.library.util.FilterType;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/9/28
 */
public class GPUImageTwoInputFilter extends NativeFilter{
    private Bitmap bitmap;

    public GPUImageTwoInputFilter() {
        this(-1,null);
    }
    public GPUImageTwoInputFilter(int filterType, Bitmap bitmap) {
        super(filterType);
        this.bitmap = bitmap;
    }

    public Bitmap getBitmap() {
        return bitmap;
    }

    public void setBitmap(Bitmap bitmap) {
        this.bitmap = bitmap;
    }
}
