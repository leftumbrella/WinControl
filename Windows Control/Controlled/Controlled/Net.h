#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_
/*
*	�������ڴ������������������
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

	//��ʼ����������
	bool Initialize(unsigned short port_num=6400);

	bool ReadNetCommand(CmdCore& cmd_core);

	Net& Send(const std::string& send_str);

	Net& Send(const char* send_cstr);

private:
	//�������ȴ�����
	void Listen();

	void RecvData();

	//��������(��ȡ������IPV4��ַ)
	std::string GetIpV4() const;

	//�������������ִ�Ϊ��������
	void CommandAnsy(const std::string& cmd_str);

private:
	_WINSOCK2API_::SOCKET _sock_recv;
	_WINSOCK2API_::SOCKET _sock_send;

	//���ƶ��˽������ݵ��߳�
	bool _isRunRecv;
	std::thread _t_recv;

	bool _is_listening;
	std::thread _t_listen;

	std::mutex _lock_command;
	std::queue<CmdCore> _command;

	//���ڴ����ʱ�������̳߳�
	boost::thread_group _TP;
};

#endif