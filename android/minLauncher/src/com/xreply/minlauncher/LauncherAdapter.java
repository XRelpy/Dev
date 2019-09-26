package com.xreply.minlauncher;

import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.ResolveInfo;
import android.graphics.drawable.Drawable;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class LauncherAdapter extends BaseAdapter {
    private final LayoutInflater mInflater;
    private final PackageManager mPm;
    private final Intent mIntent;

    private List<LauncherPackage> mLauncherPackage;
    private Context mContex;

    public LauncherAdapter(Context context) {
        mContex = context;
        mInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

        mPm = context.getPackageManager();
        mIntent = new Intent(Intent.ACTION_MAIN, null);
        mIntent.addCategory(Intent.CATEGORY_LAUNCHER); // get all apps
        mLauncherPackage = new ArrayList<>();
        getDataList();
    }

    @Override
    public int getCount() {
        return mLauncherPackage.size();
    }

    @Override
    public Object getItem(int position) {
        return mLauncherPackage.get(position);
    }

    @Override
    public long getItemId(int position) {
        return position;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup parent) {
        if (convertView == null) {
            convertView = mInflater.inflate(R.layout.app_item, parent, false);
        }
        ImageView icon = convertView.findViewById(R.id.app_icon);
        TextView title = convertView.findViewById(R.id.app_title);
        LauncherPackage splitPackage = (LauncherPackage) getItem(position);
        icon.setImageDrawable(splitPackage.icon);
        title.setText(splitPackage.title);
        return convertView;
    }

    private void getDataList() {
        mLauncherPackage.clear();
        List<ResolveInfo> apps = mPm.queryIntentActivities(mIntent, 0);
        for (ResolveInfo app : apps) {
            LauncherPackage splitPkg = new LauncherPackage();
            try {
                PackageInfo pkgInfo = mPm.getPackageInfo(app.activityInfo.packageName, PackageManager.GET_META_DATA);
                splitPkg.title = pkgInfo.applicationInfo.loadLabel(mPm).toString();
                splitPkg.icon = pkgInfo.applicationInfo.loadIcon(mPm);
                splitPkg.cn = new ComponentName(pkgInfo.packageName, app.activityInfo.name);
                mLauncherPackage.add(splitPkg);
            } catch (Exception ex) {
                Log.d("MiniLauncher", "getDataList error:" + ex.toString());
            }
        }
    }

    public class LauncherPackage {
        public String title;
        public Drawable icon;
        public ComponentName cn;
    }
}
