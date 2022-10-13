//
// Created by root on 10/12/22.
//
#include "tasks.h"

namespace audio_controller::tasks {
    Components getAudioControllerTasks() {
        return fruit::createComponent()
                .registerProvider(MAKE_TASKS_PROVIDER(ManageSpeakerAudioTask))
                .install(getAudioControllerManageSpeakerAudioTask);
    }
}