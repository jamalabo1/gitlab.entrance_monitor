//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PUBLISHER_FACTORY_H
#define ENTRANCE_MONITOR_V2_PUBLISHER_FACTORY_H

#include <string>
#include <core/init.h>
#include <core/amqp.h>
#include <core/publisher.h>

namespace core::publish {

    class PublisherFactory {
    public:
        virtual std::unique_ptr<Publisher> create_publisher(const std::string &exchange_name, amqp::ArgsTable args = {}) = 0;
    };

    using PublisherFactoryComponent = fruit::Component<RequiredComponents, PublisherFactory>;

    PublisherFactoryComponent getPublisherFactoryComponent();

}
#endif //ENTRANCE_MONITOR_V2_PUBLISHER_FACTORY_H
