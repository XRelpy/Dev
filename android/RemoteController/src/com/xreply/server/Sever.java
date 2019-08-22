package com.xreply.server;

import com.xreply.common.Utils;
import com.xreply.common.XLog;
import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.*;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.handler.codec.DelimiterBasedFrameDecoder;
import io.netty.handler.codec.Delimiters;
import io.netty.handler.codec.string.StringDecoder;
import io.netty.handler.codec.string.StringEncoder;
import io.netty.handler.logging.LogLevel;
import io.netty.handler.logging.LoggingHandler;
import io.netty.util.CharsetUtil;

public class Sever implements Runnable{
    @Override
    public void run() {
        ControllerServer();
    }

    private void ControllerServer() {
        EventLoopGroup bossGroup = new NioEventLoopGroup();
        EventLoopGroup workerGroup = new NioEventLoopGroup();
        try {
            ServerBootstrap serverBootstrap = new ServerBootstrap();
            serverBootstrap.group(bossGroup, workerGroup);
            serverBootstrap.channel(NioServerSocketChannel.class);
            serverBootstrap.option(ChannelOption.SO_BACKLOG, 1024);
            serverBootstrap.handler(new LoggingHandler(LogLevel.INFO));
            serverBootstrap.childOption(ChannelOption.TCP_NODELAY, true);
            serverBootstrap.childOption(ChannelOption.SO_KEEPALIVE, true);
            serverBootstrap.childHandler(new ChannelInitializer<SocketChannel>() {
                @Override
                public void initChannel(SocketChannel socketChannel) throws Exception {
                    ChannelPipeline pipeline = socketChannel.pipeline();
                    pipeline.addLast(new DelimiterBasedFrameDecoder(8192, Delimiters.lineDelimiter()));
                    pipeline.addLast(new StringDecoder(CharsetUtil.UTF_8));
                    pipeline.addLast(new StringEncoder(CharsetUtil.UTF_8));
                    pipeline.addLast(new RegisterController());
                }
            });
            ChannelFuture channelFuture = serverBootstrap.bind(Utils.CONNECT_REQUEST_PORT).sync();
            channelFuture.channel().closeFuture().sync();
        } catch (Exception ex) {
            XLog.D(ex.toString());
        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }

    }
}
