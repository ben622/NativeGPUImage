package com.ben.android.library;

import android.content.Context;
import android.support.annotation.NonNull;
import android.text.TextUtils;

import java.io.File;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public final class NGP {
    private static final String DEFAULT_CACHE_DIR = "ngp";
    private static boolean isInitialize;
    private static volatile NGP ngp;

    private NGPConfigure configure;

    public static NGP get(@NonNull Context context) {
        if (ngp == null) {
            synchronized (NGP.class) {
                if (ngp == null) {
                    checkInitialize(context);
                }
            }
        }
        return ngp;
    }

    public static NGP get() {
        if (ngp == null) {
            throw new NullPointerException("You have not initialized NGP yet!");
        }
        return ngp;
    }


    private static void checkInitialize(@NonNull Context context) {
        initialize(context);
    }


    public static void initialize(NGPConfigure configure) {
        if (configure.getContext() == null) {
            throw new NullPointerException("context is null!");
        }
        NGP.ngp = new NGP();
        NGP.ngp.configure = configure;
        NGP.ngp.checkCacheConfigure();
        NGP.ngp.initNGPBridge();
        NGP.isInitialize = true;
    }

    public static void initialize(Context context) {
        initialize(new NGPConfigure.ConfigurBuilder().context(context).build());
    }


    public static RenderBuilder with(@NonNull Context context) {
        return new RenderBuilder(context);
    }

    private void initNGPBridge() {
        NGPNativeBridge.init();
    }

    private void checkCacheConfigure() {
        if (ngp.configure == null) {
            throw new NullPointerException("configure null!");
        }

        if (TextUtils.isEmpty(ngp.configure.getCacheDir())) {
            ngp.configure.setCacheDir(
                    ngp.configure.getContext().getCacheDir() + File.separator + DEFAULT_CACHE_DIR
            );
        }
        File cache = new File(ngp.configure.getCacheDir());
        if (!cache.exists()) {
            cache.mkdir();
        }
    }

    public boolean clearCache() {
        boolean delFile = delFile(new File(getConfigure().getCacheDir()));
        checkCacheConfigure();
        return delFile;
    }

    private boolean delFile(File file) {
        if (!file.exists()) {
            return false;
        }

        if (file.isDirectory()) {
            File[] files = file.listFiles();
            for (File f : files) {
                delFile(f);
            }
        }
        return file.delete();
    }

    public NGPConfigure getConfigure() {
        return configure;
    }
}
