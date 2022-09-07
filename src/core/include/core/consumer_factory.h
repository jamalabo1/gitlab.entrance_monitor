//
// Created by jamal on 26/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_FACTORY_H
#define ENTRANCE_MONITOR_V2_CONSUMER_FACTORY_H

#include <core/init.h>
#include <core/amqp.h>
#include <core/consumer.h>

namespace core::consume {

    using CreateConsumerCb = std::function<void(const CancellationToken &token, const ConsumerMessageHandler &handler)>;

    class ConsumerFactory {
    public:
        virtual CreateConsumerCb create_consumer(const std::string &exchange_name, amqp::ArgsTable args = {}) = 0;
    };


    using ConsumerFactoryComponent = fruit::Component<RequiredComponents, ConsumerFactory>;

    ConsumerFactoryComponent getConsumerFactoryComponent();
}


#endif //ENTRANCE_MONITOR_V2_CONSUMER_FACTORY_H
