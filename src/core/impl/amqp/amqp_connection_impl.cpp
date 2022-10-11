//
// Created by jamal on 17/08/2022.
//
#include "amqp_connection_impl.h"

#include "amqp/io_context.h"

#include <core/logging.h>
#include <amqpcpp/libboostasio.h>


namespace core::amqp {
    namespace impl {

AmqpConnectionImpl::AmqpConnectionImpl(Configurations *configs, shared_ptr<AMQP::TcpHandler> handler) : handler_(handler) {
//    AMQP::LibBoostAsioHandler handler(*context->get_service());

    auto login = AMQP::Login(configs->get("amqp-user"), configs->get("amqp-password"));


    auto addr = AMQP::Address(configs->get("amqp-host"), configs->get<int>("amqp-port"), login, configs->get("amqp-vhost"));

    BOOST_LOG_TRIVIAL(trace) << "connecting to amqp host";
    // make a connection
    connection_ = make_unique<AMQP::TcpConnection>(handler_.get(), addr);
}

shared_ptr<AMQP::Channel> AmqpConnectionImpl::create_channel() {
    //TODO: refactor usage of pointers, because it's a mess.
    auto aconn = connection_.get();
    return make_shared<AMQP::TcpChannel>(aconn);
}

    }

AmqpConnectionComponent getAmqpConnectionComponent() {
    return fruit::createComponent()
    .registerProvider([](AmqpIoContext *ctx) -> AMQP::TcpHandler* {
        BOOST_LOG_TRIVIAL(trace) << "creating amqp handler";
        return new AMQP::LibBoostAsioHandler(*ctx->get_service());
    })
    .bind<AmqpConnection, impl::AmqpConnectionImpl>();
}
}
