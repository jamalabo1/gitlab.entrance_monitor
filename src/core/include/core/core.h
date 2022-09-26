//
// Created by jamal on 17/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CORE_H
#define ENTRANCE_MONITOR_V2_CORE_H

#include <core/init.h>
#include <core/amqp.h>
#include <core/cancellation_token.h>
#include <core/configurations.h>
#include <core/queue_fps.h>
#include <core/view.h>
#include <core/service.h>
#include <core/ptrs.h>
#include <core/gui_handler.h>
#include <core/logging.h>
#include <core/io_runner.h>
#include <core/communication.h>


namespace core {
    EXPORT_MODULE(getCoreComponents, $IoRunner, $GUIHandler, amqp::$Components, communication::$Components);
}

#endif //ENTRANCE_MONITOR_V2_CORE_H
