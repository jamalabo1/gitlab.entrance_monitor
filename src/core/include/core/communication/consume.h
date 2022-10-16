//
// Created by jamal on 21/09/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_H

#include <core/init.h>

#include "consume/consumer.h"
#include "consume/consumer_factory.h"

namespace core::communication::consume {
    EXPORT_MODULE(getCommunicationConsumeComponents, $ConsumerComponent);
}

#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_H
