//
// Created by jamal on 03/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_IMPL_H
#define ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_IMPL_H

#include "amqp/connection.h"

#include "channel_holder.h"
#include <core/logging.h>

#include <amqpcpp.h>

namespace core::amqp::impl {

    class ChannelHolderImpl : public ChannelHolder {
    private:
        shared_ptr<AMQP::Channel> channel;

        std::mutex channel_mutex;


    public:
        INJECT(ChannelHolderImpl(AmqpConnection * connection));

        shared_ptr<AMQP::Channel> operator*() const override;

        shared_ptr<AMQP::Channel> operator->() const override;

    };
}

#endif //ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_IMPL_H
