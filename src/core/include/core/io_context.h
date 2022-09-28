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
    class IoContext {
    public:

        virtual shared_ptr<boost::asio::io_context> get_context() = 0;
        virtual operator boost::asio::io_context() const = 0;
        virtual operator shared_ptr<boost::asio::io_context>() const = 0;


    };


    using $IoContext = $Exported<IoContext>;

    using IoContextComponent = $IoContext::Component<GUIHandler, amqp::AmqpIoRunner>;

    IoContextComponent getIoContextComponent();
}

#endif //ENTRANCE_MONITOR_V2_IO_RUNNER_H
