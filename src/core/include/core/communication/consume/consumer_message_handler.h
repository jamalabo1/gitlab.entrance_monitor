//
// Created by jamal on 31/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_MESSAGE_HANDLER_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_MESSAGE_HANDLER_H

#include "consumer_message.h"

namespace core::communication::consume {

    class ConsumerMessageHandler {
    public:
        virtual void operator()(const ConsumerMessage::ptr_t &envelope) const;
    };

}
#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_MESSAGE_HANDLER_H
