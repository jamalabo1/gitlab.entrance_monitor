//
// Created by jamal on 30/08/2022.
//
#include "impl/io_runner_impl.h"

using namespace fruit;
using namespace core;
using namespace core::impl;
using namespace core::amqp;

IoRunnerImpl::IoRunnerImpl(GUIHandler *gui_handler, AmqpIoRunner *amqp_io_runner) : gui_handler(
        gui_handler), amqp_io_runner(amqp_io_runner) {
    pool = make_shared<boost::asio::thread_pool>();
}

void IoRunnerImpl::setup() {


    post([&]() {
        gui_handler->run();
    });
    post([&]() {
        amqp_io_runner->run();
    });

}

void IoRunnerImpl::post(IoRunnerPostCb cb) {
    boost::asio::post(*pool, cb);
}

shared_ptr<boost::asio::thread_pool> IoRunnerImpl::get_pool() {
    return this->pool;
}

IoRunnerComponent core::getIoRunnerComponent() {
    return createComponent()
            .bind<IoRunner, IoRunnerImpl>();
}