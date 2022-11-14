//
// Created by jamal on 02/07/2022.
//
#include <core/standalone.h>
#include <stream_obtainer/stream_obtainer.h>

using namespace fruit;
using core::IoContext;
using core::getCoreComponents;
using core::getConfigurationsComponent;
using stream_obtainer::getStreamObtainerComponent;

Component<core::IoContext> getRootComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getConfigurationsComponent)
            .install(getStreamObtainerComponent);
}

BUILD_STANDALONE_FROM_SERVICE(getRootComponent);