#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_

#include <string>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#include "WinUtils.h"
#include <sstream>
#pragma comment(lib,"Ws2_32.lib ")

class Net{
public:
	Net();
	~Net();

	bool Initialize(unsigned short port_num=6400);

private:
	//¼àÌý£¬µÈ´ýÁ¬½Ó
	void Receive();

	//
	void SendVolume();

	void RecvData();

	std::string GetIpV4() const;

private:
	_WINSOCK2API_::SOCKET _sock_recv;
	_WINSOCK2API_::SOCKET _sock_send;

	bool _isRunSend;
	std::thread _t_send;

	bool _isRunRecv;
	std::thread _t_recv;

	bool _is_receiving;
	std::thread _t_receive;

};

#endif