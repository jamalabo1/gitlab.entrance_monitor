//
// Created by jamal on 02/07/2022.
//

#include <core/standalone.h>
#include <object_detector/object_detector.h>

using fruit::createComponent;
using fruit::Component;

using core::IoContext;
using core::getCoreComponents;
using core::getConfigurationsComponent;
using object_detector::getObjectDetectorComponent;

Component<core::IoContext> getRootComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getConfigurationsComponent)
            .install(getObjectDetectorComponent);
}

BUILD_STANDALONE_FROM_SERVICE(getRootComponent)