//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_PRIVATE_AMQP_H
#define ENTRANCE_MONITOR_V2_PRIVATE_AMQP_H

#include <core/amqp.h>

#include <amqpcpp.h>

AMQP::Table to_table(const core::amqp::ArgsTable& table);

#endif //ENTRANCE_MONITOR_V2_PRIVATE_AMQP_H
