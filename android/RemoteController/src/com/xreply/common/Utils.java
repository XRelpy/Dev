package com.xreply.common;

import com.google.gson.Gson;

public class Utils {
    public static final String DEFAULT_IP = "192.168.43.199";
    public static final int CONNECT_REQUEST_PORT = 10300;

    public static final int DEFAULT_GESTURE_STREAM_PORT = 10334;
    public static final int DEFAULT_SURFACE_STREAM_PORT = 10335;

    // for request
    public static final String KEY_REQUEST_GESTURE_PORT = "gesture_port";
    public static final String KEY_REQUEST_SURFACE_PORT = "surface_port";

    public static String ObjectToGson(Object o) {
        Gson gson = new Gson();
        return gson.toJson(o) + "\r\n";
    }
}
