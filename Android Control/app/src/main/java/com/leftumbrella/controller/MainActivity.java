package com.leftumbrella.controller;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.Socket;
import java.net.SocketException;
import java.util.Enumeration;



public class MainActivity extends AppCompatActivity {
    final String TAG = "LFDEBUG";

    private NetCore net_core = new NetCore();

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Window window = getWindow();
        window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);

        window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
        //设置状态栏颜色
        window.setStatusBarColor(getColor(R.color.purple_500));

        setContentView(R.layout.activity_main);

        Button btn_volume_plus = findViewById(R.id.btn_volume_plus);
        Button btn_volume_less = findViewById(R.id.btn_volume_less);
        TextView TV_volume = findViewById(R.id.TV_volume);

        //设置按钮字体
        btn_volume_plus.setText(R.string.btn_volume_plus_str);
        btn_volume_less.setText(R.string.btn_volume_less_str);


        net_core.Link2Win("192.168.0.103",6400);
        new Thread(new Runnable() {
            @Override
            public void run() {
                while (true){
                    String volume = "" + net_core.GetVolume();
                    TV_volume.setText(volume);
                }
            }
        }).start();

        btn_volume_plus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                net_core.Send("Volume plus");
            }
        });
        btn_volume_less.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                net_core.Send("Volume less");

            }
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        net_core.Uninitialize();
    }
}

