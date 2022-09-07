//
// Created by jamal on 17/08/2022.
//

#include <core/core.h>

using namespace core;
using namespace core::amqp;
using namespace core::consume;
using namespace core::publish;

CoreComponents core::getCoreComponents() {
    return fruit::createComponent()
            .install(getGUIHandlerComponent)
            .install(getConsumerComponent)
            .install(getIoRunnerComponent)
            .install(getPublisherFactoryComponent)
            .install(getAmqpIoRunnerComponent);
}