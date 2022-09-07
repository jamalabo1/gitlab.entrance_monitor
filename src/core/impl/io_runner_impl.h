//
// Created by jamal on 30/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_IO_RUNNER_IMPL_H
#define ENTRANCE_MONITOR_V2_IO_RUNNER_IMPL_H

#include <core/init.h>
#include <core/io_runner.h>
#include <core/gui_handler.h>
#include <core/amqp/amqp_io_runner.h>

namespace core::impl {
    class IoRunnerImpl : public IoRunner {
    private:
        GUIHandler *gui_handler;
        amqp::AmqpIoRunner *amqp_io_runner;
        shared_ptr<boost::asio::thread_pool> pool;

    public:

        INJECT(IoRunnerImpl(GUIHandler * , amqp::AmqpIoRunner * ));

        void setup() override;

        void post(IoRunnerPostCb cb) override;

        shared_ptr<boost::asio::thread_pool> get_pool() override;

    };
}

#endif //ENTRANCE_MONITOR_V2_IO_RUNNER_IMPL_H
