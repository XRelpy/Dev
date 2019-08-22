package com.xreply;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;

import com.xreply.client.Client;
import com.xreply.server.RemoteService;

public class MainActivity extends AppCompatActivity {
    boolean isStarted = false;
    Button mButtonServer;
    Button mButtonClient;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mButtonClient = (Button) findViewById(R.id.seg_client);
        mButtonClient.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                (new Handler()).post(new Client());
            }
        });
        mButtonServer = (Button) findViewById(R.id.seg_server);
        mButtonServer.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (!isStarted) {
                    isStarted = true;
                    startForegroundService(new Intent(MainActivity.this, RemoteService.class));
                }
            }
        });

    }
}
