package com.xreply.server;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.IBinder;

import com.xreply.MainActivity;
import com.xreply.R;

public class RemoteService extends Service {
    Handler mHandler;
    public RemoteService() {
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }

    @Override
    public void onCreate() {
        super.onCreate();
        sendNotification();
        HandlerThread thread = new HandlerThread("Service");
        thread.start();
        mHandler = new Handler(thread.getLooper());
        mHandler.post(new Sever());
    }
    private void sendNotification() {
        if (Build.VERSION.SDK_INT>=26) {
            String channelId = "channel1";
            NotificationChannel mNotificationChannel = new NotificationChannel(channelId, "remote server", NotificationManager.IMPORTANCE_DEFAULT);
            mNotificationChannel.setDescription("remote server.");
            ( (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE)).createNotificationChannel(mNotificationChannel);
            Intent intent = new Intent(this, MainActivity.class);

            Notification nf = new Notification.Builder(this, channelId)
                    .setContentTitle("Remote Service.")
                    .setContentText("")
                    .setSmallIcon(R.mipmap.ic_launcher)
                    .setContentIntent(PendingIntent.getActivities(this, 100, new Intent[]{intent}, PendingIntent.FLAG_CANCEL_CURRENT))
                    .build();
            startForeground(10, nf);
        }
    }
}
