//
// Created by jamal on 13/08/2022.
//

#include "blocking_result_message_handler.h"

#include <core/msgpacker.h>
#include <view_models/blocking_result_view.h>
#include <core/logging.h>


using namespace core;
using namespace core::consume;

BlockingResultMessageHandler::BlockingResultMessageHandler(Aggregator *aggregator) : aggregator(aggregator) {}

void BlockingResultMessageHandler::operator()(const ConsumerMessage::ptr_t &envelope) const {
    auto view = core::msgpacker::unpack<BlockingResultView>(envelope);

    BOOST_LOG_TRIVIAL(trace) << "received blocking result: " << view.result << " on timestamp " << view.frame_timestamp;

    aggregator->add(view.frame_timestamp, view.result);
}


BlockingResultMessageHandlerComponent getBlockingResultMessageHandlerComponent() {
    return fruit::createComponent()
            .bind<ConsumerMessageHandler, BlockingResultMessageHandler>();
}