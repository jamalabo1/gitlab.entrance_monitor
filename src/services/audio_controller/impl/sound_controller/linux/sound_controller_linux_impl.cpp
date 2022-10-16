//
// Created by jamal on 17/08/2022.
//

#include <core/logging.h>
#include "sound_controller_linux_impl.h"

using namespace fruit;

void SoundControllerLinuxImpl::stop() {
    BOOST_LOG_TRIVIAL(trace) << "sound_controller linux impl stop is called";
}

void SoundControllerLinuxImpl::play() {
    BOOST_LOG_TRIVIAL(trace) << "sound_controller linux impl play is called";
}


SoundControllerComponent getSoundControllerComponent() {
    return createComponent()
            .bind<SoundController, SoundControllerLinuxImpl>();
}
