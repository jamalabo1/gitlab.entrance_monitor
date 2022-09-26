//
// Created by jamal on 9/24/22.
//
#include <gtest/gtest.h>

#include "configuration_impl.h"

namespace {

class ConfigurationsImplTestFixture : public ::testing::Test {

protected:

    fruit::Injector<core::Configurations> injector;

    static fruit::Component<core::Configurations> getRootComponent() {

    }

    ConfigurationsImplTestFixture() : injector(getRootComponent) {

    }

};

}