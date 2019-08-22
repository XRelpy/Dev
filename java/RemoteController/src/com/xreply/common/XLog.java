package com.xreply.common;

public class XLog {
    private static final String TAG = "DBMARK";
    private static final boolean DEBUG = true;

    public static void D(String s) {
        if (DEBUG) {
            System.out.println(TAG + " : " + s);
        }
    }
}
