//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_H
#define ENTRANCE_MONITOR_V2_CORE_H

#include <core/init.h>
#include <core/amqp.h>
#include <core/cancellation_token.h>
#include <core/configurations.h>
#include <core/queueFps.h>
#include <core/view.h>
#include <core/task_service.h>
#include <core/ptrs.h>
#include <core/gui_handler.h>
#include <core/consumer_factory.h>
#include <core/publisher_factory.h>
#include <core/logging.h>
#include <core/io_runner.h>


namespace core {

    using CoreComponents = fruit::Component<RequiredComponents, core::consume::Consumer, core::publish::PublisherFactory, core::GUIHandler, core::amqp::AmqpIoRunner, core::IoRunner>;

    CoreComponents getCoreComponents();
}

#endif //ENTRANCE_MONITOR_V2_CORE_H
