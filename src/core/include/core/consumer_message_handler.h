//
// Created by jamal on 31/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_HANDLER_H
#define ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_HANDLER_H


#include <functional>
#include <utility>
#include <core/consumer_message.h>
#include <opencv2/core/mat.hpp>


namespace core::consume {

    class ConsumerMessageHandler {
    public:
        virtual void operator()(const ConsumerMessage::ptr_t &envelope) const;
    };

}
#endif //ENTRANCE_MONITOR_V2_CONSUMER_MESSAGE_HANDLER_H
