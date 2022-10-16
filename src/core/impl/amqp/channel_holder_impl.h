//
// Created by jamal on 03/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_IMPL_H
#define ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_IMPL_H

#include "amqp/connection.h"

#include "channel_holder.h"

#include <amqpcpp.h>

namespace core::amqp::impl {

    class ChannelHolderImpl : public ChannelHolder {
    private:

        unique_ptr<AmqpConnection> connection_;

        shared_ptr<AMQP::Channel> channel_;

    public:

        // since `AmqpConnection` does not support sharing object across multiple threads, each thread must have its
        // connection, since each thread has its own channel, it has its own connection
        INJECT(ChannelHolderImpl(unique_factory(AmqpConnection)));

        shared_ptr<AMQP::Channel> operator*() const override;

        shared_ptr<AMQP::Channel> operator->() const override;

    };
}

#endif //ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_IMPL_H
