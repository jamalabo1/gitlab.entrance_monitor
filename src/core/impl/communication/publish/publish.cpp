//
// Created by jamal on 21/09/2022.
//

#include <core/communication/publish.h>

using namespace core::communication::publish;

Components core::communication::publish::getCommunicationPublishComponents() {
    return fruit::createComponent()
            .install(getCommunicationPublisherFactoryComponent)
            .install(getCommunicationPublisherComponent);
}