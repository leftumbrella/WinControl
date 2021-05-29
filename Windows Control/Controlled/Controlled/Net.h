#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_
/*
*	此类用于处理或发送所有网络请求
*/
#include "CmdCore.h"
#include <string>
#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <WinSock2.h>
#include "WinUtils.h"
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/thread.hpp>
#pragma comment(lib,"Ws2_32.lib ")

constexpr std::time_t Wait_Net_Time_Ms = 100;

class Net{
public:
	Net();
	~Net();

	//初始化网络配置
	bool Initialize(unsigned short port_num=6400);

	bool ReadNetCommand(CmdCore& cmd_core);

	Net& Send(const std::string& send_str);

	Net& Send(const char* send_cstr);

private:
	//监听，等待连接
	void Listen();

	void RecvData();

	//辅助函数(获取本机的IPV4地址)
	std::string GetIpV4() const;

	//分析网络数据字串为具体命令
	void CommandAnsy(const std::string& cmd_str);

private:
	_WINSOCK2API_::SOCKET _sock_recv;
	_WINSOCK2API_::SOCKET _sock_send;

	//从移动端接收数据的线程
	bool _isRunRecv;
	std::thread _t_recv;

	bool _is_listening;
	std::thread _t_listen;

	std::mutex _lock_command;
	std::queue<CmdCore> _command;

	//用于处理耗时操作的线程池
	boost::thread_group _TP;
};

#endif