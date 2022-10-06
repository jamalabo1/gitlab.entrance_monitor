//
// Created by jamal on 17/08/2022.
//
#include "amqp_io_runner_impl.h"
#include <core/logging.h>

using namespace core::amqp;
using namespace core::amqp::impl;

AmqpIoRunnerImpl::AmqpIoRunnerImpl(AmqpIoContext *context) : context(context) {

}

void AmqpIoRunnerImpl::run() {
    BOOST_LOG_TRIVIAL(trace) << "running amqp/io_service from runner";
    context->get_service()->run();
    BOOST_LOG_TRIVIAL(trace) << "amqp/io_service runner finished";
}


AmqpIoRunnerComponent core::amqp::getAmqpIoRunnerComponent() {
    return fruit::createComponent()
            .install(getAmqpIoContextComponent)
            .bind<AmqpIoRunner, AmqpIoRunnerImpl>();
}