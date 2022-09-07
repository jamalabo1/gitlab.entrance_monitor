//
// Created by jamal on 15/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_H
#define ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_H

#include <core/init.h>

class SoundController {
public:
    virtual void play() = 0;

    virtual void stop() = 0;
};

using SoundControllerComponent = fruit::Component<RequiredComponents, SoundController>;

SoundControllerComponent getSoundControllerComponent();

#endif //ENTRANCE_MONITOR_V2_SOUND_CONTROLLER_H
