package com.xreply;

import com.xreply.Client.Client;
import com.xreply.common.XLog;

public class MainClient {
    public static void main(String[] args) {
        XLog.D("Start Client...");
        Runnable r = new Client();
        Thread t = new Thread(r);
        t.start();
    }
}
