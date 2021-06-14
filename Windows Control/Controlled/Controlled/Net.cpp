#include "Net.h"

Net::Net():_is_listening(false) ,_sock_recv(0),_sock_send(0) , _isRunRecv(false){
    _isRunRecv = true;
    _t_recv = std::thread(&Net::RecvData, this);
}

Net::~Net(){
    if (_is_listening) {
        _is_listening = false;
        //终止 DLL 的使用
        _WINSOCK2API_::WSACleanup();
        _t_listen.join();
    }

    //接收数据线程结束
    _isRunRecv = false;
    _t_recv.join();
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
    sockAddr.sin_addr.s_addr = _WINSOCK2API_::inet_addr(WinUtils::GetIpV4().c_str());
    sockAddr.sin_port = _WINSOCK2API_::htons(port_num);

    if (_WINSOCK2API_::bind(_sock_recv, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
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
    

    //开始监听移动端的连接命令
    _is_listening = true;
    _t_listen = std::thread(&Net::Listen, this);

    return true;
}

bool Net::ReadNetCommand(CmdCore& cmd_core){
    if (_command.empty()) {
        return false;
    }

    _lock_command.lock();
    cmd_core = _command.front();
    _command.pop();
    _lock_command.unlock();

    return true;
}

Net& Net::Send(const std::string& send_str){
    if (_sock_send) {
        _WINSOCK2API_::send(_sock_send, send_str.c_str(), send_str.size()*sizeof(char), NULL);
    }
    return *this;
}

Net& Net::Send(const char* send_cstr){
    if (_sock_send) {
        _WINSOCK2API_::send(_sock_send, send_cstr, Max_Net_Size, NULL);
    }
    return *this;
}

void Net::Listen(){
    while (_is_listening) {
        //监听移动端连接
        SOCKADDR clntAddr;
        int nSize = sizeof(SOCKADDR);
        _sock_send = _WINSOCK2API_::accept(_sock_recv, (SOCKADDR*)&clntAddr, &nSize);
    }
    
}

void Net::RecvData(){
    while (_isRunRecv) {
        char recv_data[Max_Net_Size+1];
        
        int length = _WINSOCK2API_::recv(_sock_send, recv_data, Max_Net_Size, NULL);
        if (length > 0) {
            //使用
            recv_data[Max_Net_Size] = '\0';
            //保存当前移动端命令
            CommandAnsy(recv_data);
        }
    }
}
void Net::CommandAnsy(const std::string& cmd_str){

    std::vector<std::string> cmd_strs;
    //使用"/"将网络字符串分隔开来
    boost::split(cmd_strs, cmd_str, boost::is_any_of("/") );
    //忽略莫名其妙的网络包
    if (cmd_strs.size() != 2) {
        return;
    }
    //去除网络数据尾部空格
    std::string cmd_data_str = cmd_strs.back().empty() ? "" : boost::trim_copy(cmd_strs.back());

    //安插至队列中
    _lock_command.lock();
    _command.push(std::move(CmdCore(cmd_strs.front() ,cmd_data_str)));
    _lock_command.unlock();
}
