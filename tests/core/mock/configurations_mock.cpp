//
// Created by jamal on 09/11/2022.
//

#include "configurations_mock.h"

fruit::Component<core::Configurations> getMockConfigurationComponent() {
    return fruit::createComponent()
            .bind<core::Configurations, MockConfigurationsImpl>();
}