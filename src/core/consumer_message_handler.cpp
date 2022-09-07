//
// Created by jamal on 03/08/2022.
//


#include <core/consumer_message_handler.h>
#include <core/logging.h>

void core::consume::ConsumerMessageHandler::operator()(const ConsumerMessage::ptr_t &envelope) const {
    // run on a different thread
    BOOST_LOG_TRIVIAL(fatal) << "consumer message handler not implemented";
}
