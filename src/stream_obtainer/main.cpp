#include <stream_obtainer/stream_obtainer.h>
#include <core/standalone.h>

using namespace fruit;
using namespace core;

Component<StreamObtainer> getRootComponent() {
    return createComponent()
            .install(getConfigurationsComponent)
            .install(getStreamObtainerComponent);
}

BUILD_STANDALONE_FROM_SERVICE(getRootComponent);