#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
/*
* ����ΪWindows�����࣬ͨ���������ڻ��ȡ����Windows���ܺ�״̬
*/
#include <string>
#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>
#include <WinSock2.h>

class WinUtils{

public:
	//��ȡ��ǰ����������İٷֱ�
	static unsigned int Volume();
	//���õ�ǰ���������Ϊĳ���ٷֱ�
	static bool Volume(unsigned int value);
	//��ȡ������IPV4��ַ
	static std::string GetIpV4();



};

#endif