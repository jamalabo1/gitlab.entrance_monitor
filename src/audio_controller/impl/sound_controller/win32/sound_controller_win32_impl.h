//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_WIN32_IMPL_H
#define ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_WIN32_IMPL_H

#include <windows.h>
#include <atomic>
#include <fruit/macro.h>
#include <core/configurations.h>
#include "sound_controller.h"

class SoundControllerWIN32Impl : public SoundController {
private:
    std::atomic_bool is_playing;

    shared_ptr<std::wstring> alert_sound_file;

    IAudioEndpointVolume* endpointVolume;

    float defaultVolumeDb;
    float currentVolumeDb;
    float volumeDbIncrementalStep;

    void increase();

    void reset();

    void set_volume(float volume);

public:

    INJECT(SoundControllerWIN32Impl(core::Configurations * configs));
    ~SoundControllerWIN32Impl();

    void play() override;

    void stop() override;

};

#endif //ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_WIN32_IMPL_H
