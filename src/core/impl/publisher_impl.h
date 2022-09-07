//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PUBLISHER_IMPL_H
#define ENTRANCE_MONITOR_V2_PUBLISHER_IMPL_H

#include <core/publisher.h>

#include "channel_holder.h"

namespace core::impl {

    class PublisherImpl : public core::publish::Publisher {
    protected:
        void publish_message(const std::vector<uint8_t> &data) const override;

    public:
        explicit PublisherImpl(amqp::ChannelHolder *channel, const std::string exchange_name);


    private:
        const std::string exchange_name;
        amqp::ChannelHolder *channel;
    };

}

#endif //ENTRANCE_MONITOR_V2_PUBLISHER_IMPL_H
