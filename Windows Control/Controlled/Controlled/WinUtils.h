#ifndef LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_
#define LEFTUMBRELLA_WINCONTROL_CONTROLLED_WINUTILS_H_

#include <Windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <audioclient.h>

class WinUtils{

public:
	static unsigned int Volume();
	static bool Volume(unsigned int value);




};

#endif