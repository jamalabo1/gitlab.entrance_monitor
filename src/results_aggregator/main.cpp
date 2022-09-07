//
// Created by jamal on 13/08/2022.
//

#include <utils/standalone.h>
#include <results_aggregator/results_aggregator.h>

using namespace fruit;
using namespace core;


Component<ResultsAggregatorService> getRootComponent() {
    return createComponent()
            .install(getConfigurationsComponent)
            .install(getResultsAggregatorServiceComponent);
}


BUILD_STANDALONE_FROM_SERVICE(getRootComponent);