#include "Net.h"

Net::Net():_is_receiving(false){
    
    
}

Net::~Net(){    
    if (_is_receiving) {
        _is_receiving = false;
        _t_receive.join();
    }


    //��ֹ DLL ��ʹ��
    _WINSOCK2API_::WSACleanup();
}

bool Net::Initialize(const std::string& ip_str, unsigned short port_num){
    if (ip_str.empty()) {
        return false;
    }

    //��ʼ�� DLL
    WSADATA wsaData;
    if (_WINSOCK2API_::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        return false;
    }

    //�����׽���
    _sock_recv = _WINSOCK2API_::socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (!_sock_recv) {
        return false;
    }

    //���׽���
    _WINSOCK2API_::sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
    sockAddr.sin_family = AF_INET;  //ʹ��IPv4��ַ
    sockAddr.sin_addr.s_addr = _WINSOCK2API_::inet_addr("127.0.0.1");  //�����IP��ַ
    sockAddr.sin_port = _WINSOCK2API_::htons(6400);  //�˿�

    if (_WINSOCK2API_::bind(_sock_recv, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
        std::cout << "bind failed with error " << WSAGetLastError() << std::endl;
        _WINSOCK2API_::closesocket(_sock_recv);
        _WINSOCK2API_::WSACleanup();
        return false;
    }

    //�������״̬
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
