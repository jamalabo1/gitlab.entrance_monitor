//
// Created by jamal on 14/08/2022.
//

#include <core/standalone.h>
#include <audio_controller/audio_controller.h>

using namespace core;
using namespace fruit;

using audio_controller::getAudioControllerServiceComponent;

Component<IoContext> getRootComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getConfigurationsComponent)
            .install(getAudioControllerServiceComponent);
}


BUILD_STANDALONE_FROM_SERVICE(getRootComponent)