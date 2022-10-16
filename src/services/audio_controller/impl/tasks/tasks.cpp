//
// Created by root on 10/12/22.
//
#include "tasks.h"

namespace audio_controller::tasks {
    Components getAudioControllerTasks() {
        return CORE_TASKS_CREATE_COMPONENT(AudioController, ManageSpeakerAudioTask);
    }
}