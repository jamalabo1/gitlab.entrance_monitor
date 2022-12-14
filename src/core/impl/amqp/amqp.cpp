//
// Created by jamal on 16/08/2022.
//

#include <core/amqp.h>
#include "amqp.h"

using namespace AMQP;
using namespace core::amqp;

Table core::amqp::to_table(const ArgsTable &args_table) {
    auto map = Table();

    for (const auto &item: args_table) {
        map[item.first] = item.second.value;
    }
    return map;
}

//Components core::amqp::getAmqpComponents() {
//    return fruit::createComponent()
//            .install(getAmqpIoRunnerComponent);
//}