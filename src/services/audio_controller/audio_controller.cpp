//
// Created by jamal on 14/08/2022.
//
#include "audio_controller/audio_controller.h"
#include "tasks.h"

namespace audio_controller {

    using core::getCoreComponents;
    using core::Service;
    using tasks::getAudioControllerTasks;

    AudioControllerService::AudioControllerService(const std::vector <shared_ptr<core::Task>> &tasks) {
        registerTasks(tasks);
    }

AudioControllerServiceComponent getAudioControllerServiceComponent() {
    return fruit::createComponent()
            .install(getAudioControllerTasks)
            .install(getCoreComponents)
            .addMultibinding<Service, AudioControllerService>();
}

}

