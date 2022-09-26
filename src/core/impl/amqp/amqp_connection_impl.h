//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_CONNECTION_IMPL_H
#define ENTRANCE_MONITOR_V2_AMQP_CONNECTION_IMPL_H

#include "amqp/connection.h"
#include "amqp/io_context.h"
#include <amqpcpp.h>
#include <amqpcpp/linux_tcp.h>

namespace core::amqp::impl {


    class AmqpConnectionImpl : public AmqpConnection {
    private:
        shared_ptr<AMQP::TcpConnection> connection;
        unique_ptr<AMQP::TcpHandler> handler;
    public:
        INJECT(AmqpConnectionImpl(core::Configurations * , AmqpIoContext * context));

        shared_ptr<AMQP::Channel> create_channel() override;
    };
}

#endif //ENTRANCE_MONITOR_V2_AMQP_CONNECTION_IMPL_H
