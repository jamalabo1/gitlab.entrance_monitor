//
// Created by jamal on 13/08/2022.
//


#include <utils/standalone.h>
#include <blocking_computation/blocking_computation.h>

using namespace fruit;
using namespace core;

Component<BlockingComputationService> getRootComponent() {
    return createComponent()
            .install(getConfigurationsComponent)
            .install(getBlockingComputationComponent);
}


BUILD_STANDALONE_FROM_SERVICE(getRootComponent);