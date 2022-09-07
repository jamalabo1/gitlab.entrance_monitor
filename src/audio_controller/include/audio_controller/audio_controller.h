//
// Created by jamal on 14/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AUDIO_CONTROLLER_H
#define ENTRANCE_MONITOR_V2_AUDIO_CONTROLLER_H


#include <core/core.h>

class AudioControllerService : public core::TaskService {
private:
    core::consume::ConsumerMessageHandler *handler;
    core::consume::Consumer *consumer;


public:

    INJECT(AudioControllerService(
            core::consume::ConsumerMessageHandler *,
            core::consume::Consumer * ,
            core::IoRunner *
    ));

    int setup() override;
};

using AudioControllerServiceComponent = fruit::Component<RequiredComponents, AudioControllerService>;


AudioControllerServiceComponent getAudioControllerServiceComponent();


#endif //ENTRANCE_MONITOR_V2_AUDIO_CONTROLLER_H
