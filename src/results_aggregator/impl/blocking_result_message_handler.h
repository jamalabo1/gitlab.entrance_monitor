//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_BLOCKING_RESULT_MESSAGE_HANDLER_H
#define ENTRANCE_MONITOR_V2_BLOCKING_RESULT_MESSAGE_HANDLER_H

#include <core/init.h>
#include <core/communication/consume.h>
#include "results_aggregator/aggregator.h"

class BlockingResultMessageHandler : public core::communication::consume::ConsumerMessageHandler {
private:
    Aggregator* aggregator;
public:
    INJECT(BlockingResultMessageHandler(Aggregator* aggregator));

    void operator()(const core::communication::consume::ConsumerMessage::ptr_t &envelope) const override;
};

using BlockingResultMessageHandlerComponent = fruit::Component<MakeRequiredComponents(Aggregator), core::communication::consume::ConsumerMessageHandler>;

BlockingResultMessageHandlerComponent getBlockingResultMessageHandlerComponent();

#endif //ENTRANCE_MONITOR_V2_BLOCKING_RESULT_MESSAGE_HANDLER_H
