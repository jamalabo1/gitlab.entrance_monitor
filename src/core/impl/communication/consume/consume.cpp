//
// Created by jamal on 21/09/2022.
//
#include <core/communication/consume.h>


using namespace core::communication::consume;


Components core::communication::consume::getCommunicationConsumeComponents() {
    return fruit::createComponent()
            .install(getCommunicationConsumeConsumerComponent);
}