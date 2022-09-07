//
// Created by jamal on 23/08/2022.
//

#ifndef ENTRANCE_MONITOR_V2_CONFIGURATION_IMPL_H
#define ENTRANCE_MONITOR_V2_CONFIGURATION_IMPL_H


#include <core/configurations.h>
#include <azure/keyvault/secrets.hpp>

namespace core::impl {

    class ConfigurationsImpl : public Configurations {

    private:
        Azure::Security::KeyVault::Secrets::SecretClient *m_secretsClient;

        // mutex for safe multi-threading access.
        std::mutex m_cacheMapMutex;
        std::map<std::string, std::string> m_cacheMap;


    protected:

        std::string get_value_from_key(const std::string &key) override;

    public:
        INJECT(ConfigurationsImpl(Azure::Security::KeyVault::Secrets::SecretClient * client));

    };

}

#endif //ENTRANCE_MONITOR_V2_CONFIGURATION_IMPL_H
