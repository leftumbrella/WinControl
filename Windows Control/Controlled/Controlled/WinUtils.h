#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
/*
* ����ΪWindows�����࣬ͨ���������ڻ��ȡ����Windows���ܺ�״̬
*/
#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>

class WinUtils{

public:
	//��ȡ��ǰ����������İٷֱ�
	static unsigned int Volume();
	//���õ�ǰ���������Ϊĳ���ٷֱ�
	static bool Volume(unsigned int value);




};

#endif