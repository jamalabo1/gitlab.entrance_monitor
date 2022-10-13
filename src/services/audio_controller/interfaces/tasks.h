//
// Created by root on 10/12/22.
//

#ifndef ENTRANCE_MONITOR_V2_TASKS_H
#define ENTRANCE_MONITOR_V2_TASKS_H

#include <core/init.h>

#include "tasks/manage_speaker_audio_task.h"

namespace audio_controller::tasks {
    EXPORT_TASKS_MODULE(getAudioControllerTasks, $ManageSpeakerAudioTask);
}

#endif //ENTRANCE_MONITOR_V2_TASKS_H
