package com.leftumbrella.controller;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //开始连接按钮
        Button btn = findViewById(R.id.btn_exit);
        btn.setText(R.string.btn_start_net);
        btn.setOnClickListener(
            new View.OnClickListener(){
                @Override
                public void onClick(View v){
                    finish();
                }
            }
        );
    }
}