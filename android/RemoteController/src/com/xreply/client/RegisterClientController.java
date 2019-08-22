package com.xreply.client;

import com.google.gson.Gson;
import com.xreply.common.ConnectData;
import com.xreply.common.XLog;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

public class RegisterClientController  extends SimpleChannelInboundHandler<String> {
    @Override
    protected void channelRead0(ChannelHandlerContext channelHandlerContext, String s) throws Exception {
        try {
            Gson gson = new Gson();
            ConnectData data = gson.fromJson(s, ConnectData.class);
            XLog.D("Register:" + data.GesturePort + " -- " + data.SurfacePort);
        } catch (Exception ex) {
            XLog.D(ex.toString());
        }
    }

    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        super.channelActive(ctx);
        XLog.D("Client channel Active.");
    }
}
