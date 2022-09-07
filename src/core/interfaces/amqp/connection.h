//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_CONNECTION_H
#define ENTRANCE_MONITOR_V2_AMQP_CONNECTION_H

#include <core/init.h>
#include <amqp/io_context.h>
#include <amqpcpp.h>

namespace core::amqp {

    class AmqpConnection {

    public:
        virtual shared_ptr<AMQP::Channel> create_channel() = 0;
    };


    using AmqpConnectionComponent = fruit::Component<MakeRequiredComponents(AmqpIoContext), AmqpConnection>;

    AmqpConnectionComponent getAmqpConnectionComponent();
}

#endif //ENTRANCE_MONITOR_V2_AMQP_CONNECTION_H
