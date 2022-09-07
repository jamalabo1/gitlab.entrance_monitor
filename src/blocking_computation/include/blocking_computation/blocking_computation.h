//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H
#define ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H

#include <core/core.h>


class BlockingComputationService : public core::TaskService {
private:
    core::consume::ConsumerMessageHandler *handler;
    core::consume::Consumer *consumer;

public:

    INJECT(BlockingComputationService(core::consume::ConsumerMessageHandler * ,
                                      core::consume::Consumer * , core::IoRunner * ));


    int setup() override;
};


using BlockingComputationComponent = fruit::Component<RequiredComponents, BlockingComputationService>;

BlockingComputationComponent getBlockingComputationComponent();


#endif //ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H
