package com.ben.android.library.load.engine;

import android.graphics.Bitmap;


/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class Resource {
    private Bitmap bitmap;
    private int position;

    private Resource(Bitmap bitmap, int position) {
        this.bitmap = bitmap;
        this.position = position;
    }

    public static Resource obtain(Bitmap src, int position){
        return new Resource(src,position);
    }

    public Bitmap getBitmap() {
        return bitmap;
    }

    public int getPosition() {
        return position;
    }
}
