//
// Created by jamal on 21/09/2022.
//
#include <core/communication/consume.h>

namespace core::communication::consume {
    Components getCommunicationConsumeComponents() {
        return fruit::createComponent()
                .install(getCommunicationConsumeConsumerComponent);
    }
}

