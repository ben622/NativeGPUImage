package com.ben.android.library.util;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/11
 */
public enum Rotation {
    NORMAL(0), ROTATION_90(90), ROTATION_180(180), ROTATION_270(270);
    private int value;

    public static int getValue(Rotation rotation) {
        for (Rotation item : values()) {
            if (item == rotation) {
                return item.value;
            }
        }
        return 0;
    }

    Rotation(int value) {
        this.value = value;
    }}

