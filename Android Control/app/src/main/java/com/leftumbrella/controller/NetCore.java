package com.leftumbrella.controller;

import android.util.Log;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.util.concurrent.locks.ReentrantLock;

public class NetCore {

    private Socket _sock = null;
    private int _volume = 0;

    private boolean _isRunRecv = false;
    private Thread _t_recv = null;

    public boolean Link2Win(String ip_str ,int port_num){
        new Thread(new Runnable(){
            @Override
            public void run() {
                try {
                    _sock = new Socket(ip_str, port_num);
                    _t_recv = new Thread(new Runnable() {
                        @Override
                        public void run() {
                            while (_isRunRecv){
                                try{
                                    String msg="Volume";
                                    _sock.getOutputStream().write(msg.getBytes());
                                    DataInputStream dis = new DataInputStream(_sock.getInputStream());
                                    byte[] numByte = new byte[256];
                                    int file_num = dis.read(numByte);
                                    byte[] NumByte = new byte[file_num];
                                    for(int i=0;i<file_num;++i){
                                        NumByte[i] = numByte[i];
                                    }
                                    String fileNumStr = new String(NumByte);
                                    if(fileNumStr.contains("Volume::")){
                                        fileNumStr = fileNumStr.replaceAll("Volume::","");
                                        _volume = Integer.parseInt(fileNumStr);
                                    }
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            }
                        }
                    });
                    StartRecv();
                } catch (IOException e) {
                    Log.e("LFDEBUG","init ERROR");
                    e.printStackTrace();
                }
            }
        }).start();
        return true;
    }

    public void Send(String str){
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    _sock.getOutputStream().write(str.getBytes());
                }catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

    public void StartRecv(){
        _isRunRecv = true;
        _t_recv.start();
    }



    public int GetVolume(){
        return _volume;
    }


    public void Uninitialize(){
        if(_sock!=null){
            try{
                _sock.close();
            }catch(IOException e){
                e.printStackTrace();
            }

        }
    }

}
