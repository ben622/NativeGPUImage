package com.ben.android.library.render;

import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.load.engine.Resource;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class Render {
    private NativeFilter filter;
    private Resource resource;

    private Render(NativeFilter filter, Resource resource) {
        this.filter = filter;
        this.resource = resource;
    }

    public NativeFilter getFilter() {
        return filter;
    }

    public void setFilter(NativeFilter filter) {
        this.filter = filter;
    }


    public Resource getResource() {
        return resource;
    }

    public void setResource(Resource resource) {
        this.resource = resource;
    }

    public static Render obtain(Resource resource, NativeFilter filter) {
        return new Render(filter, resource);
    }


    public static class UpgradRender {
        private NativeFilter filter;

        private UpgradRender(NativeFilter filter) {
            this.filter = filter;
        }

        public NativeFilter getFilter() {
            return filter;
        }

        public void setFilter(NativeFilter filter) {
            this.filter = filter;
        }

        public static UpgradRender obtain(Render render) {
            return obtain(render.getFilter());
        } public static UpgradRender obtain(NativeFilter filter) {
            return new UpgradRender(filter);
        }
    }
}
