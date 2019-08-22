package com.xreply.server;

import com.google.gson.Gson;
import com.xreply.common.ConnectData;
import com.xreply.common.UserData;
import com.xreply.common.Utils;
import com.xreply.common.XLog;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;

import java.net.InetSocketAddress;


public class RegisterController  extends SimpleChannelInboundHandler<String> {
    @Override
    protected void channelRead0(ChannelHandlerContext channelHandlerContext, String s) throws Exception {
        try {
            Gson gson = new Gson();
            UserData user = gson.fromJson(s, UserData.class);
            XLog.D("Register:" + user.UserName + " -- " + user.UserPassword);
            ConnectData data = new ConnectData();
            data.SurfacePort = Utils.DEFAULT_SURFACE_STREAM_PORT;
            data.GesturePort = Utils.DEFAULT_GESTURE_STREAM_PORT;

            channelHandlerContext.writeAndFlush(Utils.ObjectToGson(data));
        } catch (Exception ex) {
            channelHandlerContext.writeAndFlush("Connect Error.");
            XLog.D(ex.toString());
        }
    }

    @Override
    public void channelActive(ChannelHandlerContext ctx) throws Exception {
        super.channelActive(ctx);
        InetSocketAddress insocket = (InetSocketAddress) ctx.channel().remoteAddress();
        String clientIp = insocket.getAddress().getHostAddress();
        XLog.D("收到客户端[ip:" + clientIp + "]连接");
    }
}
