//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_LINUX_IMPL_H
#define ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_LINUX_IMPL_H

#include "sound_controller.h"

class SoundControllerLinuxImpl : public SoundController {
public:

    INJECT(SoundControllerLinuxImpl()) = default;

    void stop() override;

    void play() override;
};


#endif //ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_LINUX_IMPL_H
