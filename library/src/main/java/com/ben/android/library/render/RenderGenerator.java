package com.ben.android.library.render;


import com.ben.android.library.NGPNativeBridge;

import java.util.concurrent.LinkedBlockingQueue;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class RenderGenerator implements RenderFetcherGenerator{
    private LinkedBlockingQueue<Render> mRenderQueue = new LinkedBlockingQueue<>();
    @Override
    public void run() {
        synchronized (RenderGenerator.class) {
            try {
                Render render = mRenderQueue.take();

            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
