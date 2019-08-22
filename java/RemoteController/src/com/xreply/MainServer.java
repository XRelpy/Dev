package com.xreply;

import com.xreply.Server.Sever;
import com.xreply.common.XLog;

public class MainServer {
    public static void main(String[] args) {
        XLog.D("Start Server..");
        Runnable r = new Sever();
        Thread t = new Thread(r);
        t.start();
    }
}
