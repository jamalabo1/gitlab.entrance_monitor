//
// Created by jamal on 17/08/2022.
//
#include "amqp_connection_impl.h"
#include <amqpcpp/libboostasio.h>

using namespace core::amqp;
using namespace core::amqp::impl;

AmqpConnectionImpl::AmqpConnectionImpl(core::Configurations *configs, AmqpIoContext *context) {
//    AMQP::LibBoostAsioHandler handler(*context->get_service());

    handler = make_unique<AMQP::LibBoostAsioHandler>(*context->get_service());

    auto login = AMQP::Login(configs->get("amqp-user"), configs->get("amqp-password"));


    auto addr = AMQP::Address(configs->get("amqp-host"), configs->get<int>("amqp-port"), login, configs->get("amqp-vhost"));

    // make a connection
    connection = make_shared<AMQP::TcpConnection>(handler.get(), addr);
}

shared_ptr<AMQP::Channel> AmqpConnectionImpl::create_channel() {
    auto aconn = connection.get();
    return make_shared<AMQP::TcpChannel>(aconn);
}


AmqpConnectionComponent core::amqp::getAmqpConnectionComponent() {
    return fruit::createComponent()
            .bind<AmqpConnection, AmqpConnectionImpl>();
}
