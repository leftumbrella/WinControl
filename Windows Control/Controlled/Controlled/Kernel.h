#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_KERNEL_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_KERNEL_H_

#include "Net.h"
#include "WinUtils.h"
#include <thread>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>

class Kernel{
public:
	static Kernel* GetInstance();

	Kernel& Initialize();
	Kernel& Run();


private:
	static Kernel* _instance;
	Kernel();
	~Kernel();

	void AnsyCmd(CmdCore cmd_core);
	void ReadNetCmd();

	void SendVolume();

	void PCMonitor();

private:
	Net _net;

	bool _isRun_read_cmd;
	std::thread _t_read_cmd;

	bool _isRun_PC_monitor;
	std::thread _t_PC_monitor;

	int _volume_num;

	boost::thread_group _TP;

};

#endif