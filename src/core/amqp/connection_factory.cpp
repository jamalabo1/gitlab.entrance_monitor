//
// Created by jamal on 26/07/2022.
//

#include "amqp/connection.h"
#include "channel_holder_impl.h"
#include "amqp/io_context.h"

using namespace AMQP;

using namespace core::amqp;
using namespace core::amqp::impl;

AmqpComponent core::amqp::getAmqpComponent() {
    return fruit::createComponent()
            .install(getAmqpIoContextComponent)
            .install(getAmqpConnectionComponent)
            .bind<ChannelHolder, ChannelHolderImpl>();
}