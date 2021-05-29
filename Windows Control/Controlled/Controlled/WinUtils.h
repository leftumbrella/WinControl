#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
/*
* 此类为Windows控制类，通过它来调节或获取各项Windows功能和状态
*/
#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>

class WinUtils{

public:
	//获取当前计算机音量的百分比
	static unsigned int Volume();
	//设置当前计算机音量为某个百分比
	static bool Volume(unsigned int value);




};

#endif