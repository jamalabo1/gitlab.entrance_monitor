//
// Created by jamal on 13/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_H
#define ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_H

#include <core/ptrs.h>
#include <utility>

namespace core::consume {

    class ConsumerMessage {
    public:
        typedef shared_ptr <ConsumerMessage> ptr_t;

        virtual std::string Body() = 0;
    };
}

#endif //ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_H
