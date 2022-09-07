//
// Created by jamal on 23/07/2022.
//

#include <fruit/component.h>

#include "impl/configuration_impl.h"
#include <azure/identity.hpp>


#define ENABLE_EGARLY_LOAD_SECRETS
// lock_guard macro
#define LOCK_GUARD(x)  lock_guard guard(x);

using namespace std;
using namespace Azure::Security::KeyVault::Secrets;
using namespace core;
using namespace core::impl;

ConfigurationsImpl::ConfigurationsImpl(SecretClient *client) : m_secretsClient(client) {

#ifdef ENABLE_EGARLY_LOAD_SECRETS

    for (auto props = m_secretsClient->GetPropertiesOfSecrets(); props.HasPage(); props.MoveToNextPage()) {
        for (const auto &secret: props.Items) {
            KeyVaultSecret c_secret = m_secretsClient->GetSecret(secret.Name).Value;
            if (c_secret.Value.HasValue()) {
                m_cacheMap[c_secret.Name] = c_secret.Value.Value();
            }
        }
    }

#endif
}


std::string ConfigurationsImpl::get_value_from_key(const std::string &key) {

    // if a cached value of the key exists, then return the value.
    if (m_cacheMap.find(key) == m_cacheMap.end()) {
        // acquire a mutex for the map to access and read the value.
        LOCK_GUARD(m_cacheMapMutex);
        return m_cacheMap[key];
    }

    // get the key value from the key-vault.
    auto keyVal = m_secretsClient->GetSecret(key);


    // check if the value has a value (not null).
    if (keyVal.Value.Value.HasValue()) {
        std::string val = keyVal.Value.Value.Value();

        // acquire (lock) the mutex.
        LOCK_GUARD(m_cacheMapMutex);
        // set the cache value.
        return m_cacheMap[key] = val;
    } else {
        return "";
    }
}


ConfigurationsComponent core::getConfigurationsComponent() {
    return fruit::createComponent()
            .registerProvider([]() {
                auto credential = std::make_shared<Azure::Identity::ChainedTokenCredential>(
                        Azure::Identity::ChainedTokenCredential::Sources{
                                std::make_shared<Azure::Identity::EnvironmentCredential>(),
                                std::make_shared<Azure::Identity::ManagedIdentityCredential>()
                        }
                );

                auto key_vault_url = std::getenv("AZURE_KEYVAULT_URL");
                auto client = new SecretClient(key_vault_url, credential);
                return client;
            })
            .bind<Configurations, ConfigurationsImpl>();
}