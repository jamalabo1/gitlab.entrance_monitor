//
// Created by jamal on 03/08/2022.
//
#include "channel_holder_impl.h"

#include <core/logging.h>

using namespace core::amqp;
using namespace core::amqp::impl;

ChannelHolderImpl::ChannelHolderImpl(AmqpConnection *connection) {
    channel = connection->create_channel();
    channel->onError([](auto err){
        BOOST_LOG_TRIVIAL(fatal) << "error at channel: " << err;
    });

}

shared_ptr<AMQP::Channel> ChannelHolderImpl::operator*() const {
    return channel;
}

shared_ptr<AMQP::Channel> ChannelHolderImpl::operator->() const {
    return this->operator*();
}


AmqpChannelComponent core::amqp::getAmqpChannelComponent() {
    return fruit::createComponent()
            .install(getAmqpIoContextComponent)
            .install(getAmqpConnectionComponent)
            .bind<ChannelHolder, ChannelHolderImpl>();
}