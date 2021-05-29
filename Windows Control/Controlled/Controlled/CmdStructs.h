#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDSTRUCTS_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_CMDSTRUCTS_H_


namespace lfu {
	enum class CmdType {
		NONE = 0,			//无命令
		SHUTDOWN,			//关机
		CANCEL_SHUTDOWN,	//取消关机
		VOLUME_SET,			//设置音量
		SEND_NOW_VOLUME,	//获取当前计算机音量

	};
}

#endif