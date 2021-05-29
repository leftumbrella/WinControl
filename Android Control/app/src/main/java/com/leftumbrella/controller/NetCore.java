package com.leftumbrella.controller;

import android.util.Log;

import java.io.DataInputStream;
import java.io.IOException;
import java.net.Socket;
import java.util.Arrays;

public class NetCore {
    private final int Max_Net_Size = 512;
    private Socket _sock = null;
    private String _ip_str;
    private int _port_num = -1;
    private boolean _isRunRecv = false;
    private boolean _is_linking = false;

    //TCP连接至计算机
    public void Link2Win(String ip_str , int port_num){
        _is_linking = true;
        _ip_str = ip_str;
        _port_num = port_num;
        new Thread(() -> {
            try {
                _sock = new Socket(ip_str, port_num);
                StartRecv();
            } catch (IOException e) {
                e.printStackTrace();
            }
            Send("SEND_NOW_VOLUME");
        }).start();
        _is_linking = false;
    }

    //发送命令给计算机
    public void Send(String send_type_str){
        if(_sock==null){
            return;
        }
        byte[] net_byte = new byte[Max_Net_Size];
        Arrays.fill(net_byte , (byte)32);
        String tmp_str = send_type_str + "/";
        System.arraycopy(tmp_str.getBytes(), 0, net_byte, 0, tmp_str.length());
        new Thread(() -> {
            try {
                _sock.getOutputStream().write(net_byte);
                _sock.getOutputStream().flush();
            }catch (IOException e) {
                //尝试重新连接
                Link2Win(_ip_str ,_port_num);
                Send(send_type_str);
                e.printStackTrace();
            }
        }).start();
    }
    public void Send(String send_type_str ,String send_data_str){
        if(_sock==null){
            return;
        }
        byte[] net_byte = new byte[Max_Net_Size];
        Arrays.fill(net_byte , (byte)32);
        String msg = new String(net_byte);
        String tmp_str = send_type_str + "/" + send_data_str;
        System.arraycopy(tmp_str.getBytes(), 0, net_byte, 0, tmp_str.length());
        String msg1 = new String(net_byte);
        new Thread(() -> {
            try {
                _sock.getOutputStream().write(net_byte);
                _sock.getOutputStream().flush();
            }catch (IOException e) {
                //尝试重新连接
                Link2Win(_ip_str ,_port_num);
                Send(send_type_str,send_data_str);
                e.printStackTrace();
            }
        }).start();
    }

    //开始从计算机中接收
    public void StartRecv(){
        _isRunRecv = true;

        new Thread(() -> {
            while (_isRunRecv){
                try{
                    //接收从计算机中传输来的数据
                    DataInputStream dis = new DataInputStream(_sock.getInputStream());
                    byte[] net_byte = new byte[Max_Net_Size];
                    int net_size = dis.read(net_byte);
                    if(net_size > 0) {
                        String net_str = new String(net_byte);
                        //分析处理网络数据
                        Kernel.GetInstance().AnsyCmd(net_str);
                    }
                } catch (IOException e) {
                    PCMultimedia.GetInstance().set_volume_size(0);
                    if(!_is_linking){
                        _isRunRecv = false;
                        Link2Win(_ip_str ,_port_num);
                    }
                    e.printStackTrace();
                }
            }
        }).start();
    }

    //反初始化
    public void Uninitialize(){
        if(_sock!=null){
            try{
                _sock.close();
                _isRunRecv = false;
            }catch(IOException e){
                e.printStackTrace();
            }

        }
    }

}
