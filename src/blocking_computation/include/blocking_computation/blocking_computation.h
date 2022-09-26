//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H
#define ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H

#include <core/core.h>


class BlockingComputationService : public core::Service {
private:
    core::communication::consume::ConsumerMessageHandler *handler;
    core::communication::consume::Consumer *consumer;

public:

    INJECT(BlockingComputationService(core::communication::consume::ConsumerMessageHandler * ,
                                      core::communication::consume::Consumer * , core::IoRunner * ));


    int setup() override;
};


using BlockingComputationComponent = fruit::Component<RequiredComponents, BlockingComputationService>;

BlockingComputationComponent getBlockingComputationComponent();


#endif //ENTRANCE_MONITOR_V2_BLOCKING_COMPUTATION_H
