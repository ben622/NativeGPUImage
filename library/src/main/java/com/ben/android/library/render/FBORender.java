package com.ben.android.library.render;

import com.ben.android.library.NGPNativeBridge;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class FBORender implements IRender {
    @Override
    public void initialized() {
        NGPNativeBridge.nativeCreateGL();
        NGPNativeBridge.nativeSurfaceChanged(1080, 1920);
    }

    @Override
    public void destory() {

    }
}
