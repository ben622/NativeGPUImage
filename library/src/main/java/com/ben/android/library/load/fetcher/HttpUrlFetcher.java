package com.ben.android.library.load.fetcher;

import android.net.Uri;
import android.text.TextUtils;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.Map;

/**
 * @author @zhangchuan622@gmail.com
 * @version 1.0
 * @create 2019/10/9
 */
public class HttpUrlFetcher implements DataFetcher<InputStream> {
    private static final String TAG = HttpUrlFetcher.class.getSimpleName();
    private String url;
    private final int timeout;
    private final HttpUrlConnectionFactory connectionFactory;
    private HttpURLConnection urlConnection;
    private InputStream stream;
    private volatile boolean isCancelled;
    static final HttpUrlConnectionFactory DEFAULT_CONNECTION_FACTORY =
            new DefaultHttpUrlConnectionFactory();
    private static final String ALLOWED_URI_CHARS = "@#&=*+-_.,:!?()/~'%;$";
    private static final int INVALID_STATUS_CODE = -1;
    public HttpUrlFetcher(String url) {
        this(url,2500, DEFAULT_CONNECTION_FACTORY);
    }

    public HttpUrlFetcher(String url, int timeout, HttpUrlConnectionFactory connectionFactory) {
        this.url = url;
        this.timeout = timeout;
        this.connectionFactory = connectionFactory;
    }

    @Override
    public void loadData(DataCallback<? super InputStream> callback) {
        try {
            InputStream result = loadDataWithRedirects(new URL(Uri.encode(url, ALLOWED_URI_CHARS)), 0, null);
            callback.onDataReady(result);
        } catch (IOException e) {
            if (Log.isLoggable(TAG, Log.DEBUG)) {
                Log.d(TAG, "Failed to load data for url", e);
            }
            callback.onLoadFailed(e);
        }
    }

    @Override
    public InputStream loadData() {
        try {
            return loadDataWithRedirects(new URL(Uri.encode(url, ALLOWED_URI_CHARS)), 0, null);
        } catch (IOException e) {
            if (Log.isLoggable(TAG, Log.DEBUG)) {
                Log.d(TAG, "Failed to load data for url", e);
            }
        }
        return null;
    }

    private InputStream loadDataWithRedirects(URL url, int redirects,Map<String, String> headers) throws IOException {

        urlConnection = connectionFactory.build(url);
        if (headers != null) {
            for (Map.Entry<String, String> headerEntry : headers.entrySet()) {
                urlConnection.addRequestProperty(headerEntry.getKey(), headerEntry.getValue());
            }
        }
        urlConnection.setConnectTimeout(timeout);
        urlConnection.setReadTimeout(timeout);
        urlConnection.setUseCaches(false);
        urlConnection.setDoInput(true);

        // Stop the urlConnection instance of HttpUrlConnection from following redirects so that
        // redirects will be handled by recursive calls to this method, loadDataWithRedirects.
        urlConnection.setInstanceFollowRedirects(false);

        // Connect explicitly to avoid errors in decoders if connection fails.
        urlConnection.connect();
        // Set the stream so that it's closed in cleanup to avoid resource leaks. See #2352.
        stream = urlConnection.getInputStream();
        if (isCancelled) {
            return null;
        }
        final int statusCode = urlConnection.getResponseCode();
        if (isHttpOk(statusCode)) {
            return getStreamForSuccessfulRequest(urlConnection);
        } else if (isHttpRedirect(statusCode)) {
            String redirectUrlString = urlConnection.getHeaderField("Location");
            if (TextUtils.isEmpty(redirectUrlString)) {
                throw new HttpException("Received empty or null redirect url");
            }
            URL redirectUrl = new URL(url, redirectUrlString);
            // Closing the stream specifically is required to avoid leaking ResponseBodys in addition
            // to disconnecting the url connection below. See #2352.
            cleanup();
            return loadDataWithRedirects(redirectUrl, redirects + 1, null);
        } else if (statusCode == INVALID_STATUS_CODE) {
            throw new HttpException(statusCode);
        } else {
            throw new HttpException(urlConnection.getResponseMessage(), statusCode);
        }
    }
    private InputStream getStreamForSuccessfulRequest(HttpURLConnection urlConnection)
            throws IOException {
        if (TextUtils.isEmpty(urlConnection.getContentEncoding())) {
            int contentLength = urlConnection.getContentLength();
            stream = ContentLengthInputStream.obtain(urlConnection.getInputStream(), contentLength);
        } else {
            if (Log.isLoggable(TAG, Log.DEBUG)) {
                Log.d(TAG, "Got non empty content encoding: " + urlConnection.getContentEncoding());
            }
            stream = urlConnection.getInputStream();
        }
        return stream;
    }
    public void cleanup() {
        if (stream != null) {
            try {
                stream.close();
            } catch (IOException e) {
                // Ignore
            }
        }
        if (urlConnection != null) {
            urlConnection.disconnect();
        }
        urlConnection = null;
    }
    // Referencing constants is less clear than a simple static method.
    private static boolean isHttpOk(int statusCode) {
        return statusCode / 100 == 2;
    }

    // Referencing constants is less clear than a simple static method.
    private static boolean isHttpRedirect(int statusCode) {
        return statusCode / 100 == 3;
    }


    interface HttpUrlConnectionFactory {
        HttpURLConnection build(URL url) throws IOException;
    }

    private static class DefaultHttpUrlConnectionFactory implements HttpUrlConnectionFactory {

        DefaultHttpUrlConnectionFactory() { }

        @Override
        public HttpURLConnection build(URL url) throws IOException {
            return (HttpURLConnection) url.openConnection();
        }
    }

}
