#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_NET_H_

#include <string>
#include <iostream>
#include <thread>
#include <WinSock2.h>
#pragma comment(lib,"Ws2_32.lib ")

class Net{
public:
	Net();
	~Net();

	bool Initialize(const std::string& ip_str ,unsigned short port_num=1998);

private:
	void Receive();

private:
	_WINSOCK2API_::SOCKET _sock_recv;
	_WINSOCK2API_::SOCKET _sock_send;

	bool _is_receiving;
	std::thread _t_receive;

};

#endif