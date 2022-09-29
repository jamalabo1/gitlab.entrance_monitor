//
// Created by jamal on 30/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_IO_RUNNER_H
#define ENTRANCE_MONITOR_V2_IO_RUNNER_H

#include <core/init.h>
#include <boost/asio.hpp>

#define GET_BOOST_IO_CONTEXT(ctx) *(ctx)->get_context()

namespace core {
    class IoContext {
    public:

        virtual shared_ptr<boost::asio::io_context> get_context() = 0;

        virtual operator shared_ptr<boost::asio::io_context>() const = 0;

        virtual size_t run() = 0;

    };


    using $IoContext = $Exported<IoContext>;

    using IoContextComponent = $IoContext::PureComponent;

    IoContextComponent getIoContextComponent();
}

#endif //ENTRANCE_MONITOR_V2_IO_RUNNER_H
