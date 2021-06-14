#include "WinUtils.h"

unsigned int WinUtils::Volume(){
    HRESULT is_ok = E_FAIL;
    IMMDeviceEnumerator* device_enumerator_ptr = nullptr;
    is_ok = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(is_ok)) {
        return 105;
    }

    is_ok = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&device_enumerator_ptr);
    if (FAILED(is_ok)) {
        return 101;
    }

    IMMDevice* device_ptr = nullptr;
    is_ok = device_enumerator_ptr->GetDefaultAudioEndpoint(eRender, eMultimedia, &device_ptr);
    if (FAILED(is_ok)) {
        return 102;
    }

    IAudioEndpointVolume* audio_ptr = nullptr;
    is_ok = device_ptr->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&audio_ptr);
    if (FAILED(is_ok)) {
        return 103;
    }

    float volume_value = 0.0F;
    is_ok = audio_ptr->GetMasterVolumeLevelScalar(&volume_value);
    if (FAILED(is_ok)) {
        return 104;
    }

    return static_cast<unsigned int>(volume_value * 100.0F + 0.5F);
}

bool WinUtils::Volume(unsigned int value){
    if (value > 100) {
        return false;
    }

    HRESULT is_ok = E_FAIL;
    IMMDeviceEnumerator* device_enumerator_ptr = nullptr;
    is_ok = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&device_enumerator_ptr);
    if (FAILED(is_ok)) {
        return false;
    }

    IMMDevice* device_ptr = nullptr;
    is_ok = device_enumerator_ptr->GetDefaultAudioEndpoint(eRender, eMultimedia, &device_ptr);
    if (FAILED(is_ok)) {
        return false;
    }

    IAudioEndpointVolume* audio_ptr = nullptr;
    is_ok = device_ptr->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&audio_ptr);
    if (FAILED(is_ok)) {
        return false;
    }

    float value_volume = static_cast<float>(value) / 100.0F;
    audio_ptr->SetMasterVolumeLevelScalar(value_volume, &GUID_NULL);
    if (FAILED(is_ok)) {
        return false;
    }

    return true;
}

std::string WinUtils::GetIpV4(){
    std::string ipv4_str;

    char host_name[256];
    //获取本机主机名称
    int iRet;
    iRet = _WINSOCK2API_::gethostname(host_name, 256);
    if (iRet != 0) {
        return ipv4_str;
    }
    //通过主机名获取到地址信息
    _WINSOCK2API_::HOSTENT* host = _WINSOCK2API_::gethostbyname(host_name);
    if (nullptr == host) {
        return ipv4_str;
    }
    _WINSOCK2API_::in_addr address;
    for (int i = 0;; i++) {
        char* p = host->h_addr_list[i];
        if (NULL == p) {
            break;
        }
        memcpy(&(address.S_un.S_addr), p, host->h_length);
        ipv4_str = _WINSOCK2API_::inet_ntoa(address);
    }
    return ipv4_str;
}
