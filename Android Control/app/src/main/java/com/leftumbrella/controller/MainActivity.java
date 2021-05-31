package com.leftumbrella.controller;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.app.ProgressDialog;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.SeekBar;
import android.widget.TextView;


public class MainActivity extends AppCompatActivity {
    //与计算机的网络通信类
    private final NetCore _net_core = new NetCore();
    //在未连接至网络时的遮罩对话框
    private ProgressDialog _pd_link = null;
    //这个handler用于当失去连接时显示进度遮罩对话框
    private Handler _hd_no_link = null;
    //这个线程用于监视与计算机的网络连接状态
    private Thread _t_look_link_status = null;
    private boolean _is_look_link_status_running = false;
    //刷新界面音量显示的线程
    private Thread _t_flush_volume = null;
    private boolean _is_flush_volume_running = false;

    private boolean _is_moving_volume_skb = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Window window = getWindow();
        window.clearFlags(WindowManager.LayoutParams.FLAG_TRANSLUCENT_STATUS);
        window.addFlags(WindowManager.LayoutParams.FLAG_DRAWS_SYSTEM_BAR_BACKGROUNDS);
        //设置状态栏颜色
        window.setStatusBarColor(getColor(R.color.purple_500));
        setContentView(R.layout.activity_main);

        //设置连接计算机网络时显示的遮罩对话框的属性
        {
            _pd_link = new ProgressDialog(this);
            _pd_link.setTitle(null);
            _pd_link.setIcon(null);
            _pd_link.setMessage("正在等待计算机远程连接...");
            _pd_link.setCancelable(false);
            _pd_link.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        }

        //设置失去连接handle
        _hd_no_link = new Handler(new Handler.Callback() {
            @Override
            public boolean handleMessage(@NonNull Message msg) {
                //当what为1时，代表失去了与计算机的网络连接，那么应该显示遮罩进度对话框
                if(msg.what==1){
                    _pd_link.show();
                    return false;
                }
                return true;
            }
        });

        Button btn_shutdown = findViewById(R.id.btn_shutdown);
        Button btn_cancel_shutdown = findViewById(R.id.btn_cancel_shutdown);
        TextView TV_volume = findViewById(R.id.TV_volume);
        SeekBar skb_volume_change = findViewById(R.id.SKB_volume_change);
        EditText etn_shutdown_time = findViewById(R.id.etn_shutdown_time);

        //初始化刷新界面音量显示的线程
        _t_flush_volume = new Thread(() -> {
            while (_is_flush_volume_running){
                if(_is_moving_volume_skb){
                    continue;
                }
                int volume_size = PCMultimedia.GetInstance().get_volume_size();
                String volume_str = "" + volume_size;
                if(volume_str!=TV_volume.getText()){
                    TV_volume.setText(volume_str);
                }
                if(volume_size!=skb_volume_change.getProgress()){
                    skb_volume_change.setProgress(volume_size);
                }
            }
        });


        //设置网络连接状态监视线程
        _t_look_link_status = new Thread(()->{
            while (_is_look_link_status_running){
                //如果连接完成，做一系列操作
                if(_net_core.is_is_link_over()){
                    whenLinkUp();
                //如果连接断开，显示对话框
                }else{
                    if(!_pd_link.isShowing()){
                        Message msg_show_pd_link = new Message();
                        msg_show_pd_link.what = 1;
                        _hd_no_link.sendMessage(msg_show_pd_link);
                    }
                }
            }
        });

        //运行监视线程，并尝试连接至计算机
        _is_look_link_status_running = true;
        _t_look_link_status.start();
        _net_core.Link2Win("192.168.0.103",6400);

        //关机按钮点击事件
        btn_shutdown.setOnClickListener(
                v->{
                    String time_shutdown_str = etn_shutdown_time.getText().toString();
                    if(time_shutdown_str.isEmpty()){
                        return;
                    }

                    _net_core.Send("SHUTDOWN",time_shutdown_str);
                }
        );
        //取消关机按钮点击事件
        btn_cancel_shutdown.setOnClickListener(v->_net_core.Send("CANCEL_SHUTDOWN"));

        skb_volume_change.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            //音量拖动条变动事件
            @Override
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                if(fromUser){
                    TV_volume.setText(""+progress);
                    _net_core.Send("VOLUME_SET",""+seekBar.getProgress());
                }
            }

            @Override
            public void onStartTrackingTouch(SeekBar seekBar) {
                _is_moving_volume_skb = true;
            }

            @Override
            public void onStopTrackingTouch(SeekBar seekBar) {
                _is_moving_volume_skb = false;
            }
        });
    }

    private void whenLinkUp(){
        //取消显示遮罩对话框
        if(_pd_link.isShowing()) {
            //获取计算机音量
            _net_core.Send("SEND_NOW_VOLUME");
            _pd_link.dismiss();
        }

        if(!_t_flush_volume.isAlive()){
            //开始音量刷新线程
            _is_flush_volume_running = true;
            _t_flush_volume.start();
        }
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

        //等待线程结束运行
        try {
            _is_flush_volume_running = false;
            _is_look_link_status_running = false;
            _t_look_link_status.join();
            _t_flush_volume.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        _net_core.Uninitialize();
    }
}

