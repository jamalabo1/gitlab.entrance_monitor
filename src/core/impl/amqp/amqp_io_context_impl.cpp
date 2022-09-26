//
// Created by jamal on 17/08/2022.
//

#include <amqpcpp.h>
#include "amqp_io_context_impl.h"

using namespace boost::asio;
using namespace core::amqp;
using namespace core::amqp::impl;


AmqpIoContextImpl::AmqpIoContextImpl() {
    service = make_shared<io_context>(4);
}

shared_ptr<io_context> AmqpIoContextImpl::get_service() {
    return service;
}

AmqpIoContextComponent core::amqp::getAmqpIoContextComponent() {
    return fruit::createComponent()
            .bind<AmqpIoContext, AmqpIoContextImpl>();
}