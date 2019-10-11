package com.ben.android.library;

import android.content.Context;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/11
 */
public class NGPConfigure {
    private Context context;
    private String cacheDir;


    public NGPConfigure(ConfigurBuilder configurBuilder) {
        this.context = configurBuilder.context;
        this.cacheDir = configurBuilder.cacheDir;
    }

    public Context getContext() {
        return context;
    }

    public String getCacheDir() {
        return cacheDir;
    }

    public void setCacheDir(String cacheDir) {
        this.cacheDir = cacheDir;
    }

    public static class ConfigurBuilder {
        private Context context;
        private String cacheDir;

        public ConfigurBuilder context(Context context) {
            this.context = context;
            return this;
        }

        public ConfigurBuilder cacheDir(String cacheDir) {
            this.cacheDir = cacheDir;
            return this;
        }

        public NGPConfigure build() {
            return new NGPConfigure(this);
        }
    }


}
