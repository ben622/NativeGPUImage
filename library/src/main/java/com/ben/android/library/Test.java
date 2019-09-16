package com.ben.android.library;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

import java.nio.ByteBuffer;

public class Test {
    public void test() {
        Bitmap bitmap = null;
        int bytes = bitmap.getByteCount();
        ByteBuffer buffer = ByteBuffer.allocate(bytes);
        bitmap.copyPixelsToBuffer(buffer); //Move the byte data to the buffer
        byte[] data = buffer.array();
    }
    public native static void start(byte[] data);
}
