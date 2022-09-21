//
// Created by jamal on 03/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H
#define ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H

//#include <functional>
#include <core/init.h>

#include <amqpcpp.h>

// CCD = CORE CHANNEL DEFERRED
#define CCD(x) (*x)

namespace core::amqp {


    class ChannelHolder {
    public:

        virtual ~ChannelHolder() = default;

        virtual shared_ptr<AMQP::Channel> operator*() const = 0;

        virtual shared_ptr<AMQP::Channel> operator->() const = 0;

    };

    using $AmqpChannel = $Exported<ChannelHolder, std::function<std::unique_ptr<ChannelHolder>()>>;

    using AmqpChannelComponent = $AmqpChannel::PureComponent;

    AmqpChannelComponent getAmqpChannelComponent();
}

#endif //ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H
