package com.ben.android.library;

import android.content.Context;
import android.support.annotation.NonNull;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class NGP {
    private static boolean isInitialize;
    private static volatile NGP ngp;

    /**
     * get the singleton ngp.
     * @param context
     * @return
     */
    public static NGP get(@NonNull Context context){
        if (ngp == null) {
            synchronized (NGP.class){
                if (ngp == null) {
                    checkInitialize(context);
                }
            }
        }
        return ngp;
    }


    private static void checkInitialize(@NonNull Context context) {

    }

    private static void initializeNGP(@NonNull Context context){
        isInitialize = true;

    }


    public static RenderManager with(@NonNull Context context) {
        return null;
    }
}
