package com.ben.android.library.load.engine;

import android.graphics.Bitmap;


/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class Resource {
    private Bitmap bitmap;

    private Resource(Bitmap bitmap) {
        this.bitmap = bitmap;
    }

    public static Resource obtain(Bitmap src){
        return new Resource(src);
    }

    public Bitmap getBitmap() {
        return bitmap;
    }
}
