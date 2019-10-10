package com.ben.android.library.render;

import com.ben.android.library.filter.NativeFilter;
import com.ben.android.library.load.engine.Resource;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class Render  {
    private NativeFilter filter;
    private int position;
    private Resource resource;

    private Render(NativeFilter filter, int position, Resource resource) {
        this.filter = filter;
        this.position = position;
        this.resource = resource;
    }

    public NativeFilter getFilter() {
        return filter;
    }

    public void setFilter(NativeFilter filter) {
        this.filter = filter;
    }

    public int getPosition() {
        return position;
    }

    public void setPosition(int position) {
        this.position = position;
    }

    public Resource getResource() {
        return resource;
    }

    public void setResource(Resource resource) {
        this.resource = resource;
    }
    public static Render obtain(Resource resource,NativeFilter filter, int position){
        return new Render(filter, position, resource);
    }
}
