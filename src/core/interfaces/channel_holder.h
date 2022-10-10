//
// Created by jamal on 03/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H
#define ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H

//#include <functional>
#include <core/init.h>

#include <boost/asio.hpp>

#include <amqpcpp.h>

// CCD = CORE CHANNEL DEFERRED
#define CCD(x) (*x)

namespace core::amqp {


    class ChannelHolder {
    public:

        virtual ~ChannelHolder() = default;

        virtual shared_ptr<AMQP::Channel> operator*() const = 0;

        virtual shared_ptr<AMQP::Channel> operator->() const = 0;

//        template <typename CompletionToken>
//         boost::asio::async_result<boost::asio::decay<CompletionToken>,
//        void(boost::system::error_code, size_t)
//        >
//        declareQueue(
//                tcp::socket& s,
//                const mutable_buffer& b,
//                CompletionToken&& token) = 0;

    };

//    using Factory = std::function<std::unique_ptr<ChannelHolder>()>;

    using Factory = unique_factory(ChannelHolder);

    using $Channel = $Exported<ChannelHolder, Factory>;

    using AmqpChannelComponent = $Channel::PureComponent;

    AmqpChannelComponent getAmqpChannelComponent();
}

#endif //ENTRANCE_MONITOR_V2_CHANNEL_HOLDER_H
