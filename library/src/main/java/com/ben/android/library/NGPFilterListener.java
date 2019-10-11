package com.ben.android.library;

import com.ben.android.library.render.Render;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public interface NGPFilterListener {
    Render.UpgradRender apply(Render.UpgradRender render, int position);
}
