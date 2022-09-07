//
// Created by jamal on 02/07/2022.
//

#include <utils/standalone.h>
#include <object_detector/object_detector.h>

using namespace fruit;
using namespace core;

Component<ObjectDetector> getRootComponent() {
    return createComponent()
            .install(getConfigurationsComponent)
            .install(getObjectDetectorComponent);
}



BUILD_STANDALONE_FROM_SERVICE(getRootComponent)