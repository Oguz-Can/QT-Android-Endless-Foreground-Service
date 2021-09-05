package com.service.classes;

import android.app.Notification;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.app.Service;
import android.content.ComponentName;
import android.content.Context;
import android.content.pm.PackageManager;
import android.content.pm.ServiceInfo;
import android.content.Intent;
import android.os.Bundle;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;
import android.os.Process;
import android.widget.Toast;
import android.graphics.BitmapFactory;
import android.content.Context;
import android.content.Intent;
import android.os.Build;
import android.graphics.Color;
import java.security.SecureRandom;
import org.qtproject.qt5.android.bindings.QtService;
import android.support.v4.app.NotificationCompat;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;

public class MyService extends QtService
{
    private static String channelId = "com.service.classes";
    private static String channelName = "MyService";
    private static SecureRandom secureRandomGenerator = new SecureRandom();
    private IBinder mBinder = new MyBinder();
    private static int pid = secureRandomGenerator.nextInt(10000); //Should be ok to use something constant most of the time;

    public static void startMyService(Context ctx) {
        ctx.startService(new Intent(ctx, MyService.class));
    }

    @Override
    public void onCreate (){

        Log.w(getClass().getName(), "Service created ...");
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent intent) {
        Log.w(getClass().getName(), "onBind ...");
        return mBinder;
    }

    @Override
    public void onRebind(Intent intent) {
        Log.w(getClass().getName(), "onRebind ...");
        super.onRebind(intent);
    }

    @Override
    public boolean onUnbind(Intent intent) {
        Log.w(getClass().getName(), "onUnbind ...");
        return true;
    }

    public class MyBinder extends Binder {
        MyService getService() {
            return MyService.this;
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId){
        Log.w(getClass().getName(), "START ATTEMPT");

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O)
        {
            Log.w(getClass().getName(), "ANDROID OREO");
            NotificationChannel channel = new NotificationChannel(channelId, channelName, NotificationManager.IMPORTANCE_MAX);
            channel.setLightColor(Color.BLUE);
            channel.setLockscreenVisibility(Notification.VISIBILITY_PRIVATE);
            NotificationManager manager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
            manager.createNotificationChannel(channel);
        }
        else
        {
            Log.w(getClass().getName(), "ANDROID OTHER");
        }

        Context context = getApplicationContext();
        PendingIntent pi = PendingIntent.getActivity(context, 0, intent, 0);
        NotificationCompat.Builder notificationBuilder = new NotificationCompat.Builder(this, channelId);
        Notification notification = notificationBuilder
                    .setOngoing(true)
                    .setWhen(System.currentTimeMillis())
                    .setSmallIcon(R.drawable.icon)
                    .setLargeIcon(BitmapFactory.decodeResource(context.getResources(),R.drawable.icon))
                    .setContentTitle("Foreground service created")
                    .setPriority(NotificationManager.IMPORTANCE_MAX)
                    .setCategory(Notification.CATEGORY_SERVICE)
                    .setFullScreenIntent(pi, true)
                    .build();

        notification.flags = Notification.FLAG_NO_CLEAR;
        startForeground(pid, notification);

        // Set wakelock to keep cpu runnning
        PowerManager pm = (PowerManager)getSystemService(Context.POWER_SERVICE);
        WakeLock wl = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, "TestLock");
        wl.acquire();

        return START_STICKY;
    }

    @Override
    public void onDestroy(){
        Log.w(getClass().getName(), "SERVICE DESTROYED");
        super.onDestroy();
        stopForeground(true);
        stopSelf();
        //Process.killProcess(pid);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O)
        {
            NotificationManager notificationManager = (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);
            notificationManager.deleteNotificationChannel(channelId);
        }
    }

    public static void stopMyService(Context ctx){
        ctx.stopService(new Intent(ctx, MyService.class));
        }

    public static void notify(String s){
        // TO DO: update notification
    }
}
