//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_IO_CONTEXT_IMPL_H
#define ENTRANCE_MONITOR_V2_AMQP_IO_CONTEXT_IMPL_H

#include "amqp/io_context.h"
#include <core/init.h>

namespace core::amqp::impl {

    class AmqpIoContextImpl : public AmqpIoContext {
    private:
        shared_ptr<boost::asio::io_context> service;
    public:
        INJECT(AmqpIoContextImpl());

        shared_ptr<boost::asio::io_context> get_service() override;

    };
}

#endif //ENTRANCE_MONITOR_V2_AMQP_IO_CONTEXT_IMPL_H
