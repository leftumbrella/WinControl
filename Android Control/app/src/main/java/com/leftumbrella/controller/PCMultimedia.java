package com.leftumbrella.controller;

public class PCMultimedia {
    private static PCMultimedia _instance = null;

    public int get_volume_size() {
        return _volume_size;
    }

    public void set_volume_size(int _volume_size) {
        this._volume_size = _volume_size;
    }

    //计算机音量百分比
    private int _volume_size = 0;

    private PCMultimedia(){

    }

    public void AnsyMultimedia(String cmd_type_str ,String cmd_data){

        switch (cmd_type_str){
            //音量大小百分比
            case "NOW_VOLUME":
                if(!cmd_data.isEmpty()){
                    _volume_size = Integer.parseInt(cmd_data.trim());
                }
                break;
            default: break;
        }
    }

    public static PCMultimedia GetInstance(){
        if(_instance==null){
            _instance = new PCMultimedia();
        }
        return _instance;
    }



}
