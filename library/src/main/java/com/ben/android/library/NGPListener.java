package com.ben.android.library;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public interface NGPListener {
    void onRenderStart();

    void onRenderFinish();

    void onRender(Result result);
}
