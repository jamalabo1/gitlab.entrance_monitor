//
// Created by jamal on 31/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_IMPL_H
#define ENTRANCE_MONITOR_V2_CONSUMER_IMPL_H

#include <fruit/fruit.h>
#include <core/consumer.h>
#include "channel_holder.h"

namespace core::impl {

    class ConsumerImpl : public consume::Consumer {

    public:
        INJECT(ConsumerImpl(unique_factory(amqp::ChannelHolder) channel_factory)) {
            this->channel = channel_factory();
        }

        void
        consume(const consume::ConsumeOptions &) override;


    private:
        shared_ptr<amqp::ChannelHolder> channel;
        const std::string queue_name;
    };
}

#endif //ENTRANCE_MONITOR_V2_CONSUMER_IMPL_H
