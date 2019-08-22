package com.xreply.Client;


import com.google.gson.Gson;
import com.xreply.Server.RegisterController;
import com.xreply.common.UserData;
import com.xreply.common.Utils;
import com.xreply.common.XLog;
import io.netty.bootstrap.Bootstrap;
import io.netty.channel.*;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.channel.socket.nio.NioSocketChannel;
import io.netty.handler.codec.DelimiterBasedFrameDecoder;
import io.netty.handler.codec.Delimiters;
import io.netty.handler.codec.string.StringDecoder;
import io.netty.handler.codec.string.StringEncoder;
import io.netty.util.CharsetUtil;

public class Client implements Runnable {
    @Override
    public void run() {
        ClientRegister();
    }

    private void ClientRegister() {
        EventLoopGroup group = new NioEventLoopGroup();
        try {
            Bootstrap bootstrap = new Bootstrap();
            bootstrap.group(group).channel(NioSocketChannel.class);
            bootstrap.option(ChannelOption.TCP_NODELAY, true);
            bootstrap.handler(new ChannelInitializer<SocketChannel>() {
                @Override
                protected void initChannel(SocketChannel socketChannel) throws Exception {
                    ChannelPipeline pipeline = socketChannel.pipeline();
                    //pipeline.addLast(new DelimiterBasedFrameDecoder(8192, Delimiters.lineDelimiter()));
                    pipeline.addLast(new StringDecoder(CharsetUtil.UTF_8));
                    pipeline.addLast(new StringEncoder(CharsetUtil.UTF_8));
                    pipeline.addLast(new RegisterClientController());
                }
            });

            Channel channel = bootstrap.connect(Utils.DEFAULT_IP, Utils.CONNECT_REQUEST_PORT).sync().channel();
            UserData data = new UserData();
            data.UserName = "Test";
            data.UserPassword = "123456";
            Gson gson = new Gson();
            String jsonString = gson.toJson(data);
            channel.writeAndFlush(jsonString + "\r\n");
            channel.closeFuture().sync();
        } catch (Exception ex) {
            XLog.D(ex.toString());
        } finally {
            group.shutdownGracefully();
        }

    }
}
