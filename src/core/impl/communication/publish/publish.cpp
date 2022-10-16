//
// Created by jamal on 21/09/2022.
//

#include <core/communication/publish.h>

namespace core::communication::publish {
    Components getCommunicationPublishComponents() {
        return fruit::createComponent()
                .install(getCommunicationPublisherFactoryComponent)
                .install(getCommunicationPublisherComponent);
    }
}
