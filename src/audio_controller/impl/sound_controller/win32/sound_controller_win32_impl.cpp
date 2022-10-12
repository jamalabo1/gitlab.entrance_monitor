//
// Created by jamal on 17/08/2022.
//
#include <core/logging.h>
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#pragma comment(lib, "winmm.lib")

#include "sound_controller_impl.h"

void SoundControllerWIN32Impl::play() {
    increase();
    BOOST_LOG_TRIVIAL(trace) << "playing sound from sound_controller";
    bool result = PlaySound(alert_sound_file->c_str(), NULL,
                            SND_SYSTEM | SND_NODEFAULT | SND_FILENAME | SND_ASYNC |
                            SND_NOSTOP);

    is_playing = result;
    BOOST_LOG_TRIVIAL(trace) << "PlaySoundW returned " << result;
}

void SoundControllerWIN32Impl::stop() {
    reset();
    if (is_playing) {
        BOOST_LOG_TRIVIAL(trace) << "stopping sound from sound_controller";
        bool result = PlaySound(NULL, NULL, SND_ASYNC);
        BOOST_LOG_TRIVIAL(trace) << "PlaySoundW returned " << result;
        is_playing = false;
    }
}

void SoundControllerWIN32Impl::increase() {
    set_volume(currentVolumeDb + volumeDbIncrementalStep);
}

void SoundControllerWIN32Impl::reset() {
    set_volume(defaultVolumeDb);
}

void SoundControllerWIN32Impl::set_volume(float volume) {
    BOOST_LOG_TRIVIAL(trace) << "setting sound volume to: " << volume;
    currentVolumeDb = volume;
    endpointVolume->SetMasterVolumeLevel(volume, NULL);
}

SoundControllerWIN32Impl::SoundControllerWIN32Impl(Configurations *configs) {

    auto path = std::filesystem::absolute(configs->get("alert-sound-file"));
    std::wstring path_str_local = path.wstring();

    shared_ptr<std::wstring> path_str = make_shared<std::wstring>(path_str_local);

    BOOST_LOG_TRIVIAL(debug) << "audio_sound_file absolute path is: " << path;

    this->alert_sound_file = path_str;

    CoInitialize(NULL);
    HRESULT hr;
    IMMDeviceEnumerator *deviceEnumerator = NULL;
    hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator),
                          (LPVOID *) &deviceEnumerator);
    IMMDevice *defaultDevice = NULL;

    hr = deviceEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &defaultDevice);
    deviceEnumerator->Release();
    deviceEnumerator = NULL;

    wchar_t *deviceId = NULL;
    defaultDevice->GetId(&deviceId);

    BOOST_LOG_TRIVIAL(debug) << "using audio endpoint: " << deviceId;

    IAudioEndpointVolume *endpointVolume = NULL;
    hr = defaultDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, NULL,
                                 (LPVOID *) &endpointVolume);
    defaultDevice->Release();
    defaultDevice = NULL;

    this->endpointVolume = endpointVolume;


    float pflVolumeMindB, pflVolumeMaxdB;

    endpointVolume->GetVolumeRange(
            &pflVolumeMindB,
            &pflVolumeMaxdB,
            &volumeDbIncrementalStep
    );

    // min+step*n = max
    // step * n = max - min
    // n = (max-min)/step
    // db = min + step * x;

    // db_max = min + step * n;

    defaultVolumeDb = pflVolumeMindB + (float(0.9) * (pflVolumeMaxdB - pflVolumeMindB));

    currentVolumeDb = defaultVolumeDb;

    // db = min + 80%(((max-min))
    // db = min + 4/5(max-min)
    // db = (2/5)min + 3/5(max)

    //0.8 => 80%;

    // [min, max] => step;
    // min+step*n=max
    // step*n=max-min
    // I want to perform 20% of these step increments
    // n = ((max-min)/step)
    // , min = 20, max=80, step=5, 60/5 = 12
    // start at 20 + 12 * 5
    // 12 = 100%
    // db = 20 + 80%*(12*5)
}

SoundControllerWIN32Impl::~SoundControllerWIN32Impl() {
    endpointVolume->Release();

    CoUninitialize();
}


SoundControllerComponent getSoundControllerComponent() {
    return fruit::createComponent()
            .bind<SoundController, SoundControllerWIN32Impl>();
}
