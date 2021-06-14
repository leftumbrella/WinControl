#include "Kernel.h"
Kernel* Kernel::_instance = nullptr;
Kernel* Kernel::GetInstance(){
	if (_instance == nullptr) {
		_instance = new Kernel;
	}
	return _instance;
}

Kernel& Kernel::Initialize(){
	_net.Initialize();
	return *this;
}

Kernel& Kernel::Run(){
	_isRun_read_cmd = true;
	_t_read_cmd = std::thread(&Kernel::ReadNetCmd, this);

	_isRun_PC_monitor = true;
	_t_PC_monitor = std::thread(&Kernel::PCMonitor, this);

	return *this;
}

Kernel::Kernel() :_isRun_read_cmd(false){

}

Kernel::~Kernel(){
	_isRun_read_cmd = false;
	_t_read_cmd.join();
}

void Kernel::AnsyCmd(CmdCore cmd_core){
	switch (cmd_core.Type()) {
		case lfu::CmdType::SEND_NOW_VOLUME:
			SendVolume();
			break;
		case lfu::CmdType::VOLUME_SET:
			WinUtils::Volume(boost::lexical_cast<int>(cmd_core.Data()));
			SendVolume();
			break;
		case lfu::CmdType::SHUTDOWN: {
			std::stringstream ss;
			ss << "shutdown /s /t " << boost::lexical_cast<int>(cmd_core.Data());
			system(ss.str().c_str());
			break;
		}
		case lfu::CmdType::CANCEL_SHUTDOWN:
			system("shutdown /a");
			break;
	}
}

void Kernel::ReadNetCmd() {

	while (_isRun_read_cmd) {
		CmdCore cmd_data;
		if (!_net.ReadNetCommand(cmd_data)) {
			Sleep(100);
			continue;
		}
		AnsyCmd(cmd_data);
	}

}

void Kernel::SendVolume(){
	int volume_size = WinUtils::Volume();

	char send_str[Max_Net_Size];
	std::memset(send_str, ' ', Max_Net_Size);

	std::stringstream ss;
	ss << "NOW_VOLUME/" << volume_size ;
	
	std::memcpy(send_str, ss.str().c_str(), ss.str().size());

	_net.Send(send_str);
}

void Kernel::PCMonitor(){
	while (_isRun_PC_monitor){
		bool has_change = false;

		int volume_num = WinUtils::Volume();
		if (_volume_num != volume_num) {
			has_change = true;
			_volume_num = volume_num;
			SendVolume();
		}

		if (!has_change) {
			Sleep(100);
		}

	}
}
