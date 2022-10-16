//
// Created by jamal on 26/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_FACTORY_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_FACTORY_H

#include <core/init.h>
#include <core/amqp.h>
#include "consumer.h"

namespace core::communication::consume {

    using CreateConsumerCb = std::function<void(const CancellationToken &token, const ConsumerMessageHandler &handler)>;

    class ConsumerFactory {
    public:
        virtual CreateConsumerCb create_consumer(const std::string &exchange_name, amqp::ArgsTable args = {}) = 0;
    };


    using $ConsumerFactoryComponent = $Exported<ConsumerFactory>;
    using ConsumerFactoryComponent = $ConsumerFactoryComponent::PureComponent;

    ConsumerFactoryComponent getConsumerFactoryComponent();
}


#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_CONSUME_FACTORY_H
