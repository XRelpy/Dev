package com.xreply.common;

import android.util.Log;

public class XLog {
    private static final String TAG = "DBMARK";
    private static final boolean DEBUG = true;

    public static void D(String s) {
        if (DEBUG) {
            Log.d(TAG, s);
        }
    }
}
