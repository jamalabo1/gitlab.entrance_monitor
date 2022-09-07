//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PUBLISHER_FACTORY_IMPL_H
#define ENTRANCE_MONITOR_V2_PUBLISHER_FACTORY_IMPL_H

#include <fruit/fruit.h>
#include <string>
#include <core/configurations.h>
#include <core/publisher.h>
#include <core/publisher_factory.h>

#include "channel_holder.h"


namespace core::impl {

class PublisherFactoryImpl : public publish::PublisherFactory {
    private:
        amqp::ChannelHolder *channel;

    public:
        INJECT(PublisherFactoryImpl(amqp::ChannelHolder * channel))
                : channel(channel) {
        }


        unique_ptr<publish::Publisher> create_publisher(const std::string &exchange_name, amqp::ArgsTable args) override;
    };

}


#endif //ENTRANCE_MONITOR_V2_PUBLISHER_FACTORY_IMPL_H
