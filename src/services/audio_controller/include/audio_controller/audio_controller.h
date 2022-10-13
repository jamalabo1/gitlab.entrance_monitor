//
// Created by jamal on 14/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AUDIO_CONTROLLER_H
#define ENTRANCE_MONITOR_V2_AUDIO_CONTROLLER_H


#include <core/core.h>


namespace audio_controller {


    class AudioControllerService : public core::Service {
    public:

        INJECT(AudioControllerService(
                       const std::vector<shared_ptr<core::Task>>&
               ));

    };


    using $AudioController = $Exported<AudioControllerService>;

    using AudioControllerServiceComponent = $AudioController::PureComponent;

    AudioControllerServiceComponent getAudioControllerServiceComponent();

}


#endif //ENTRANCE_MONITOR_V2_AUDIO_CONTROLLER_H
