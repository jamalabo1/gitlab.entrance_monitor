//
// Created by jamal on 02/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_FACTORY_IMPL_H
#define ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_FACTORY_IMPL_H

#include <core/init.h>
#include <core/communication/publish.h>

#include "channel_holder.h"


namespace core::communication::publish::impl {

    class PublisherFactoryImpl : public PublisherFactory {
    public:
        using publisher_factory_t = std::function<std::unique_ptr<Publisher>(std::string)>;

    private:
        unique_ptr<amqp::ChannelHolder> m_channel;
        const publisher_factory_t &m_publisher_factory;
    public:

        INJECT(PublisherFactoryImpl(unique_factory(amqp::ChannelHolder), publisher_factory_t & publisher_factory));


        std::unique_ptr<Publisher>
        create_publisher(const std::string &exchange_name, amqp::ArgsTable args) const override;
    };

}


#endif //ENTRANCE_MONITOR_V2_CORE_COMMUNICATION_PUBLISH_FACTORY_IMPL_H
