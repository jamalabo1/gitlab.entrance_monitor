//
// Created by jamal on 17/08/2022.
//

#include <core/core.h>

using fruit::createComponent;

using core::getGUIHandlerComponent;
using core::getIoContextComponent;
//using core::amqp::getAmqpComponents;
using core::communication::getCommunicationComponents;
using core::retry::getRetryComponents;

core::Components core::getCoreComponents() {
    return createComponent()
            .install(getGUIHandlerComponent)
            .install(getIoContextComponent)
            .install(getCommunicationComponents)
//            .install(getAmqpComponents)
            .install(getRetryComponents);
}