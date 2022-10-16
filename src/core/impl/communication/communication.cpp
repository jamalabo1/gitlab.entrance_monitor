//
// Created by jamal on 20/09/2022.
//
#include <core/communication.h>


namespace core::communication {
    Components getCommunicationComponents() {
        return fruit::createComponent()
                .install(publish::getCommunicationPublishComponents)
                .install(consume::getCommunicationConsumeComponents);
    }
}
