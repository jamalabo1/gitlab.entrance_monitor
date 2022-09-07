//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_IO_RUNNER_H
#define ENTRANCE_MONITOR_V2_AMQP_IO_RUNNER_H

#include <core/init.h>

namespace core::amqp {

    class AmqpIoRunner {
    public:
        virtual void run() = 0;
    };

    using AmqpIoRunnerComponent = fruit::Component<RequiredComponents, AmqpIoRunner>;

    AmqpIoRunnerComponent getAmqpIoRunnerComponent();
}

#endif //ENTRANCE_MONITOR_V2_AMQP_IO_RUNNER_H
