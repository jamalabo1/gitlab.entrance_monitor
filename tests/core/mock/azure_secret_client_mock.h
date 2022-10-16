//
// Created by root on 9/24/22.
//

#ifndef ENTRANCE_MONITOR_V2_TESTS_CORE_AZURE_SECRET_CLIENT_MOCK_H
#define ENTRANCE_MONITOR_V2_TESTS_CORE_AZURE_SECRET_CLIENT_MOCK_H

//#include <gtest/mock
#define TESTING_BUILD
#include <azure/keyvault/secrets.hpp>
#include <gmock/gmock.h>

class SecretClientMock : public Azure::Security::KeyVault::Secrets::SecretClient {

};

#endif //ENTRANCE_MONITOR_V2_TESTS_CORE_AZURE_SECRET_CLIENT_MOCK_H
