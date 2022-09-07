//
// Created by jamal on 14/08/2022.
//

#include <utils/standalone.h>
#include <audio_controller/audio_controller.h>

using namespace core;
using namespace fruit;

Component<AudioControllerService> getRootComponent() {
    return createComponent()
            .install(getConfigurationsComponent)
            .install(getAudioControllerServiceComponent);
}


BUILD_STANDALONE_FROM_SERVICE(getRootComponent)