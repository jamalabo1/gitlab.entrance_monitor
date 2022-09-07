//
// Created by jamal on 16/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_AMQP_H
#define ENTRANCE_MONITOR_V2_AMQP_H

#include <map>
#include <string>
#include <core/amqp/connection_factory.h>
#include <core/amqp/amqp_io_runner.h>


namespace core::amqp {
    class ArgsTableValue;

    typedef std::map<std::string, ArgsTableValue> ArgsTable;

    class ArgsTableValue {
    public:
        int value;

        ArgsTableValue() = default;

        ArgsTableValue(const ArgsTable &value) {

        };

        ArgsTableValue(int value) {
            this->value = value;
        }
    };

}

#endif //ENTRANCE_MONITOR_V2_AMQP_H
