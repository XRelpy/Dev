package com.xreply.minlauncher;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;

public class MainActivity extends AppCompatActivity {
    private GridView mMainGrid;
    private LauncherAdapter mAdapter;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mMainGrid = (GridView) findViewById(R.id.main);
        mAdapter = new LauncherAdapter(this.getApplicationContext());
        mMainGrid.setAdapter(mAdapter);
        mMainGrid.setOnItemClickListener(mOnItemClick);
    }

    private AdapterView.OnItemClickListener mOnItemClick = new AdapterView.OnItemClickListener() {
        @Override
        public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
            LauncherAdapter.LauncherPackage pkg = (LauncherAdapter.LauncherPackage)mAdapter.getItem(position);
            Intent i = new Intent();
            i.setComponent(pkg.cn);
            startActivity(i);
        }
    };
}
