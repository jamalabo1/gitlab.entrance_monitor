//
// Created by jamal on 13/08/2022.
//


#include <core/standalone.h>
#include <blocking_computation/blocking_computation.h>

using namespace fruit;
using namespace core;
using blocking_computation::getBlockingComputationComponent;

Component<IoContext> getRootComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getConfigurationsComponent)
            .install(getBlockingComputationComponent);
}


BUILD_STANDALONE_FROM_SERVICE(getRootComponent);