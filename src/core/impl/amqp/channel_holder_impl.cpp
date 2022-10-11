//
// Created by jamal on 03/08/2022.
//
#include "channel_holder_impl.h"

#include <core/logging.h>
#include <utils/reference_time.h>

namespace core::amqp {

    namespace impl {



ChannelHolderImpl::ChannelHolderImpl(unique_factory(AmqpConnection) connection_factory)   {
    // create a connection for this channel (thread)
    connection_ = connection_factory();

    channel_ = connection_->create_channel();
    channel_->onError([](auto err){
        BOOST_LOG_TRIVIAL(fatal) << "error at channel: " << err << " at time " << utils::reference_time::getCurrentTimestamp();
    });
}

shared_ptr<AMQP::Channel> ChannelHolderImpl::operator*() const {
    return channel_;
}

shared_ptr<AMQP::Channel> ChannelHolderImpl::operator->() const {
    return this->operator*();
}

    }
AmqpChannelComponent getAmqpChannelComponent() {
    return fruit::createComponent()
            .install(getAmqpIoContextComponent)
            .install(getAmqpConnectionComponent)
            .bind<ChannelHolder, impl::ChannelHolderImpl>();
}
 }
