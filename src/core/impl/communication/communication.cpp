//
// Created by jamal on 20/09/2022.
//
#include <core/communication.h>


using namespace core::communication;


Components core::communication::getCommunicationComponents() {
    return fruit::createComponent()
            .install(publish::getCommunicationPublishComponents)
            .install(consume::getCommunicationConsumeComponents);
}