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
