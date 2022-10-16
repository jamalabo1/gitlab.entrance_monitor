//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_CONNECTION_IMPL_H
#define ENTRANCE_MONITOR_V2_AMQP_CONNECTION_IMPL_H

#include "amqp/connection.h"
#include <amqpcpp/linux_tcp.h>

namespace core::amqp::impl {


    class AmqpConnectionImpl : public AmqpConnection {
    private:
        // the handler is shared between threads;
        shared_ptr<AMQP::TcpHandler> handler_;

        // each thread has it own connection
        unique_ptr<AMQP::TcpConnection> connection_;
    public:
        INJECT(AmqpConnectionImpl(core::Configurations * , shared_ptr<AMQP::TcpHandler>));

        shared_ptr<AMQP::Channel> create_channel() override;
    };
}

#endif //ENTRANCE_MONITOR_V2_AMQP_CONNECTION_IMPL_H
