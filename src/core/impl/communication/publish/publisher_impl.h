//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_CORE_COMMUNICATION_V2_PUBLISHER_IMPL_H
#define ENTRANCE_MONITOR_CORE_COMMUNICATION_V2_PUBLISHER_IMPL_H

#include <core/init.h>
#include <core/communication/publish.h>

#include "channel_holder.h"

namespace core::communication::publish::impl {

    class PublisherImpl : public core::communication::publish::Publisher {
    protected:
        void publish_message(const std::vector<uint8_t> &data) const override;

    public:
        INJECT(PublisherImpl(ASSISTED(std::string), unique_factory(amqp::ChannelHolder)));


    private:
        const std::string exchange_name;
        unique_ptr<amqp::ChannelHolder> channel;
    };
}

#endif //ENTRANCE_MONITOR_CORE_COMMUNICATION_V2_PUBLISHER_IMPL_H
