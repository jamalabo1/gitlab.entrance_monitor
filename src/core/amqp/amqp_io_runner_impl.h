//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_IO_RUNNER_IMPL_H
#define ENTRANCE_MONITOR_V2_AMQP_IO_RUNNER_IMPL_H

#include "amqp/io_context.h"
#include <core/amqp/amqp_io_runner.h>

namespace core::amqp::impl {

    class AmqpIoRunnerImpl : public AmqpIoRunner {
    private:
        AmqpIoContext *context;
    public:
        INJECT(AmqpIoRunnerImpl(AmqpIoContext * context));

        void run() override;
    };

}

#endif //ENTRANCE_MONITOR_V2_AMQP_IO_RUNNER_IMPL_H
