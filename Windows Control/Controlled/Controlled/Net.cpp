#include "Net.h"

Net::Net():_is_receiving(false){
    
    
}

Net::~Net(){    
    if (_is_receiving) {
        _is_receiving = false;
        _t_receive.join();
    }


    //终止 DLL 的使用
    _WINSOCK2API_::WSACleanup();
}

bool Net::Initialize(const std::string& ip_str, unsigned short port_num){
    if (ip_str.empty()) {
        return false;
    }

    //初始化 DLL
    WSADATA wsaData;
    if (_WINSOCK2API_::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return false;
    }

    //创建套接字
    _sock_recv = _WINSOCK2API_::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (!_sock_recv) {
        return false;
    }

    //绑定套接字
    _WINSOCK2API_::sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = AF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = _WINSOCK2API_::inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = _WINSOCK2API_::htons(6400);  //端口

    if (_WINSOCK2API_::bind(_sock_recv, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        std::cout << "bind failed with error " << WSAGetLastError() << std::endl;
        _WINSOCK2API_::closesocket(_sock_recv);
        _WINSOCK2API_::WSACleanup();
        return false;
    }

    //进入监听状态
    if (_WINSOCK2API_::listen(_sock_recv, 20) != 0) {
        _WINSOCK2API_::closesocket(_sock_recv);
        _WINSOCK2API_::WSACleanup();
        return false;
    }

    _is_receiving = true;
    _t_receive = std::thread(&Net::Receive, this);

    return true;
}

void Net::Receive(){
    while (_is_receiving) {
        if (!_sock_recv) {
            continue;
        }
        SOCKADDR clntAddr;
        int nSize = sizeof(SOCKADDR);
        _sock_send = _WINSOCK2API_::accept(_sock_recv, (SOCKADDR*)&clntAddr, &nSize);
        char* str = "Hello World!";
        int res = _WINSOCK2API_::send(_sock_send, str, strlen(str)*sizeof(char), NULL);
    }
    
}
