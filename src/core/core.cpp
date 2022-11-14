//
// Created by jamal on 17/08/2022.
//

#include <core/core.h>

namespace core {
    using fruit::createComponent;
    using retry::getRetryComponents;
    using communication::getCommunicationComponents;

    Components getCoreComponents() {
        return createComponent()
                .install(getGUIHandlerComponent)
                .install(getIoContextComponent)
                .install(getCommunicationComponents)
                .install(getRetryComponents);
    }
}
