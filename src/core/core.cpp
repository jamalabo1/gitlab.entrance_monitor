//
// Created by jamal on 17/08/2022.
//

#include <core/core.h>

using namespace core;
using namespace core::amqp;
using namespace core::communication;

core::Components core::getCoreComponents() {
    return fruit::createComponent()
            .install(getGUIHandlerComponent)
            .install(getIoRunnerComponent)
            .install(getCommunicationComponents)
            .install(getAmqpComponents);
}