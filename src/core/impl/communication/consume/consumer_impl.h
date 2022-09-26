//
// Created by jamal on 31/07/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONSUMER_IMPL_H
#define ENTRANCE_MONITOR_V2_CONSUMER_IMPL_H

#include <core/communication/consume/consumer.h>
#include "channel_holder.h"

namespace core::communication::consume::impl {

    class ConsumerImpl : public Consumer {

    public:
        INJECT(ConsumerImpl(unique_factory(amqp::ChannelHolder) channel_factory)) {
            this->channel = channel_factory();
        }

        void consume(const ConsumeOptions &) override;


    private:
        shared_ptr<amqp::ChannelHolder> channel;
    };
}

#endif //ENTRANCE_MONITOR_V2_CONSUMER_IMPL_H
