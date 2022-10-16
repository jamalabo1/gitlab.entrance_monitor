//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_MESSAGE_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_MESSAGE_H

#include <core/init.h>

namespace core::communication::consume {

    class ConsumerMessage {
    public:
        typedef shared_ptr<ConsumerMessage> ptr_t;

        virtual std::string Body() = 0;
    };

}

#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_MESSAGE_H
