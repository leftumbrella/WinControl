package com.leftumbrella.controller;

/*
    此类是单例类
    此类用于处理和储存网络中的命令或数据与操作
 */


import android.util.Log;

public class Kernel {

    private static Kernel _instance = null;


    private Kernel() {

    }

    public void AnsyCmd(String cmd_str){
        //分割字符串
        String[] cmd_data_str = cmd_str.split("/");
        //所有网络包都被‘/’分隔为三部分
        if(cmd_data_str.length!=2){
            return;
        }
        Log.d("LFTEST" ,"类型："+cmd_data_str[0]+"/数据："+cmd_data_str[1]);

        switch (cmd_data_str[0]){
            //多媒体相关
            case "NOW_VOLUME":
                PCMultimedia.GetInstance().AnsyMultimedia(cmd_data_str[0],cmd_data_str[1]);
                break;
            default:    break;
        }




    }

    public static Kernel GetInstance() {
        if (_instance == null) {
            _instance = new Kernel();
        }
        return _instance;
    }

}
