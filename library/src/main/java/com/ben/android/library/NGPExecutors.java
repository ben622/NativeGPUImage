package com.ben.android.library;

import android.support.annotation.NonNull;

import com.ben.android.library.load.engine.Resource;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Future;
import java.util.concurrent.RejectedExecutionHandler;
import java.util.concurrent.ThreadFactory;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/10
 */
public final class NGPExecutors {
    private static final int CORE_POOL_SIZE = Runtime.getRuntime().availableProcessors() * 2;
    private static final int maximum_pool_size = CORE_POOL_SIZE;
    private static final long KEEP_ALIVE_TIME = 0;
    private static final BlockingQueue<Runnable> queue = new ArrayBlockingQueue<>(512);
    private static final RejectedExecutionHandler policy = new ThreadPoolExecutor.DiscardPolicy();
    private static final NGPThreadFactory threadFactry = new NGPThreadFactory();
    private static final ExecutorService executorService = new ThreadPoolExecutor(
            CORE_POOL_SIZE,
            maximum_pool_size,
            KEEP_ALIVE_TIME,
            TimeUnit.SECONDS,
            queue,
            policy
    );

    public static void execute(Runnable t){
        executorService.execute(t);
    }

    @NonNull
    public static Resource submit(Callable<Resource> callable) {
        Future<Resource> future = executorService.submit(callable);
        try {
           return future.get();
        } catch (ExecutionException e) {
            e.printStackTrace();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        return null;
    }

    private static class NGPThreadFactory implements ThreadFactory {
        @Override
        public Thread newThread(Runnable r) {
            return null;
        }
    }


}
