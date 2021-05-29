package com.leftumbrella.controller;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.TextView;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.Socket;
import java.net.SocketException;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class MainActivity extends AppCompatActivity {
    private final NetCore net_core = new NetCore();
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
        Button btn_shutdown = findViewById(R.id.btn_shutdown);
        Button btn_cancel_shutdown = findViewById(R.id.btn_cancel_shutdown);
        TextView TV_volume = findViewById(R.id.TV_volume);
        SeekBar skb_volume_change = findViewById(R.id.SKB_volume_change);


        //设置按钮字体
        btn_volume_plus.setText(R.string.btn_volume_plus_str);
        btn_volume_less.setText(R.string.btn_volume_less_str);

        //连接计算机网络
        net_core.Link2Win("192.168.0.103",6400);

        //开启读取并显示音量的线程
        new Thread(() -> {
            while (true){
                    int volume_size = PCMultimedia.GetInstance().get_volume_size();
                    String volume_str = "" + volume_size;
                    if(volume_str!=TV_volume.getText()){
                        TV_volume.setText(volume_str);
                    }
                    if(volume_size!=skb_volume_change.getProgress()){
                        skb_volume_change.setProgress(volume_size);
                    }
            }
        }).start();

        //关机按钮点击事件
        btn_shutdown.setOnClickListener(v->net_core.Send("SHUTDOWN","60"));
        //取消关机按钮点击事件
        btn_cancel_shutdown.setOnClickListener(v->net_core.Send("CANCEL_SHUTDOWN"));
        //音量加按钮点击事件
        btn_volume_plus.setOnClickListener(
                v ->{
                    int volume_size = PCMultimedia.GetInstance().get_volume_size();
                    if(volume_size==100){
                        return;
                    }
                    String volume_str = "" + (volume_size+1);
                    net_core.Send("VOLUME_SET",volume_str);
                }
        );
        //音量减按钮点击事件
        btn_volume_less.setOnClickListener(
            v->{
                int volume_size = PCMultimedia.GetInstance().get_volume_size();
                if(volume_size==0){
                    return;
                }
                String volume_str = "" + (volume_size-1);
                net_core.Send("VOLUME_SET",volume_str);
            }
        );

        skb_volume_change.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            //音量拖动条变动事件
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if(fromUser){
                    String progress_str = "" + progress;
                    net_core.Send("VOLUME_SET",""+seekBar.getProgress());
                }

            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {

            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {

            }
        });
    }


    @Override
    protected void onDestroy() {
        super.onDestroy();
        net_core.Uninitialize();
    }
}

