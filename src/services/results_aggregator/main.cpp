//
// Created by jamal on 13/08/2022.
//

#include <core/standalone.h>
#include <results_aggregator/results_aggregator.h>

using fruit::createComponent;
using fruit::Component;

using namespace core;
using results_aggregator::getResultsAggregatorServiceComponent;

Component<IoContext> getRootComponent() {
    return createComponent()
            .install(getCoreComponents)
            .install(getConfigurationsComponent)
            .install(getResultsAggregatorServiceComponent);
}


BUILD_STANDALONE_FROM_SERVICE(getRootComponent);