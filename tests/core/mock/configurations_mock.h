//
// Created by jamal on 16/10/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONFIGURATIONS_MOCK_H
#define ENTRANCE_MONITOR_V2_CONFIGURATIONS_MOCK_H

#include <core/configurations.h>

class MockConfigurationsImpl : public core::Configurations {
public:
    std::string get_value_from_key(const std::string &key) override {
        return "value-from-key";
    }

    INJECT(MockConfigurationsImpl()) = default;
};

fruit::Component<core::Configurations> getMockConfigurationComponent();

#endif //ENTRANCE_MONITOR_V2_CONFIGURATIONS_MOCK_H
