//
// Created by jamal on 30/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_IO_RUNNER_H
#define ENTRANCE_MONITOR_V2_IO_RUNNER_H

#include <boost/asio.hpp>
#include <core/gui_handler.h>
#include <core/amqp.h>
#include <functional>

namespace core {
    class IoRunner {
    public:
        using IoRunnerPostCb = std::function<void()>;

        virtual void setup() = 0;
        virtual void post(IoRunnerPostCb cb) = 0;

        virtual shared_ptr<boost::asio::thread_pool> get_pool() = 0;
    };


    using $IoRunner = $Exported<IoRunner>;

    using IoRunnerComponent = $IoRunner::Component<GUIHandler, amqp::AmqpIoRunner>;

    IoRunnerComponent getIoRunnerComponent();
}

#endif //ENTRANCE_MONITOR_V2_IO_RUNNER_H
