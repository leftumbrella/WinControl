#include "Net.h"

Net::Net():_is_receiving(false), _isRunSend(false) ,_sock_recv(0),_sock_send(0) , _isRunRecv(false){
    
}

Net::~Net(){    
    if (_is_receiving) {
        //终止 DLL 的使用
        _WINSOCK2API_::WSACleanup();
        _is_receiving = false;
        _t_receive.join();
    }
}

bool Net::Initialize(unsigned short port_num){

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
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_addr.s_addr = _WINSOCK2API_::inet_addr(GetIpV4().c_str());
    sockAddr.sin_port = _WINSOCK2API_::htons(port_num);

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
        if (!_isRunRecv) {
            _isRunRecv = true;
            _t_recv = std::thread(&Net::RecvData, this);
        }
    }
    
}


void Net::SendVolume(){
        if (_sock_send) {
            unsigned int now_volume = WinUtils::Volume();
            std::stringstream ss_str;
            ss_str << "Volume::" << now_volume;
            int a = _WINSOCK2API_::send(_sock_send, ss_str.str().c_str(), strlen(ss_str.str().c_str()) * sizeof(char), NULL);
        }
}

void Net::RecvData(){
    while (_isRunRecv) {
        if (_sock_send) {
            char recv_data[512];
            int length = _WINSOCK2API_::recv(_sock_send, recv_data, 512, NULL);
            if (length > 0) {
                std::string str_command = recv_data;
                if (str_command == "Volume") {
                    SendVolume();
                }else if (str_command == "Volume plus") {
                    WinUtils::Volume(WinUtils::Volume() + 1);
                }else if (str_command == "Volume less") {
                    WinUtils::Volume(WinUtils::Volume() - 1);
                }
            }
        }
    }
}

std::string Net::GetIpV4() const{

    std::string ipv4_str;

    char host_name[256];
    //获取本机主机名称
    int iRet;
    iRet = _WINSOCK2API_::gethostname(host_name, 256);
    if(iRet != 0){
        return ipv4_str;
    }
    //通过主机名获取到地址信息
    _WINSOCK2API_::HOSTENT* host = _WINSOCK2API_::gethostbyname(host_name);
    if(nullptr == host){
        return ipv4_str;
    }
    _WINSOCK2API_::in_addr address;
    for(int i = 0;; i++){
        char* p = host->h_addr_list[i];
        if(NULL == p){
            break;
        }
        memcpy(&(address.S_un.S_addr), p, host->h_length);
        ipv4_str = _WINSOCK2API_::inet_ntoa(address);
    }
    return ipv4_str;
}
