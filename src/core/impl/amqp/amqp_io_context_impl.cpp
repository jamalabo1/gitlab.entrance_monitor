//
// Created by jamal on 17/08/2022.
//

#include <amqpcpp.h>
#include "amqp_io_context_impl.h"

using namespace boost::asio;
using namespace core::amqp;
using namespace core::amqp::impl;


AmqpIoContextImpl::AmqpIoContextImpl(shared_ptr<core::IoContext> ctx) : ctx_(ctx) {

}

shared_ptr<io_context> AmqpIoContextImpl::get_service() {
    return ctx_->get_context();
}



AmqpIoContextComponent core::amqp::getAmqpIoContextComponent() {
    return fruit::createComponent()
            .install(core::getIoContextComponent)
            .bind<AmqpIoContext, AmqpIoContextImpl>();
}