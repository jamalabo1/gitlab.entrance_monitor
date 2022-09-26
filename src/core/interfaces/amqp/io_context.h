//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_IO_CONTEXT_H
#define ENTRANCE_MONITOR_V2_AMQP_IO_CONTEXT_H

#include <core/init.h>
#include <boost/asio.hpp>

namespace core::amqp {

    class AmqpIoContext {
    public:
        virtual shared_ptr<boost::asio::io_context> get_service() = 0;
    };


    using $IoContext = $Exported<AmqpIoContext>;
    using AmqpIoContextComponent = $IoContext::PureComponent;

    AmqpIoContextComponent getAmqpIoContextComponent();
}
#endif //ENTRANCE_MONITOR_V2_AMQP_IO_CONTEXT_H
