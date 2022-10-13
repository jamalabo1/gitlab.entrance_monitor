//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H
#define ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H

#include <core/core.h>

namespace blocking_computation {

class BlockingComputationService : public core::Service {
public:

    INJECT(BlockingComputationService(
                   const std::vector<shared_ptr<core::Task>>&
            ));
};


    using $BlockingComputation = $Exported<BlockingComputationService>;
    using BlockingComputationComponent = $BlockingComputation::PureComponent;
    BlockingComputationComponent getBlockingComputationComponent();
}


#endif //ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H
