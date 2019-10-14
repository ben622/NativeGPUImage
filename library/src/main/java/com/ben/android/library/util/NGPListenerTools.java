package com.ben.android.library.util;

import com.ben.android.library.NGPListener;
import com.ben.android.library.Result;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/14
 */
public class NGPListenerTools {
   public static void callRenderStart(NGPListener listener){
       if (listener != null) {
           listener.onRenderStart();
       }

   }

   public static void callRenderFinish(NGPListener listener){
       if (listener != null) {
           listener.onRenderFinish();
       }
   }

   public static void callRenderComplete(NGPListener listener,Result result){
       if (listener != null) {
           listener.onRender(result);
       }
   }
}
