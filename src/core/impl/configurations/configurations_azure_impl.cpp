//
// Created by jamal on 23/07/2022.
//


#include "configurations_azure_impl.h"

#include <core/logging.h>

#include <azure/identity.hpp>


#define ENABLE_EGARLY_LOAD_SECRETS true
// lock_guard macro

namespace core {
    using namespace Azure::Security::KeyVault::Secrets;

    namespace impl {
        using std::string;
        using std::lock_guard;

#define LOCK_GUARD(x)  lock_guard guard(x);


        ConfigurationsAzureImpl::ConfigurationsAzureImpl(SecretClient *client) : m_secretsClient(client) {

#if ENABLE_EGARLY_LOAD_SECRETS
            BOOST_LOG_TRIVIAL(trace) << "loading secrets from key-vault";
            for (auto props = m_secretsClient->GetPropertiesOfSecrets(); props.HasPage(); props.MoveToNextPage()) {
                for (const auto &secret: props.Items) {
                    KeyVaultSecret c_secret = m_secretsClient->GetSecret(secret.Name).Value;
                    if (c_secret.Value.HasValue()) {
                        m_cacheMap[c_secret.Name] = c_secret.Value.Value();
                    }
                }
            }
            BOOST_LOG_TRIVIAL(trace) << "finished secrets from key-vault";
#endif

        }


        string ConfigurationsAzureImpl::get_value_from_key(const string &key) {

            // if a cached value of the key exists, then return the value.
            if (m_cacheMap.find(key) != m_cacheMap.end()) {
                // acquire a mutex for the map to access and read the value.
                LOCK_GUARD(m_cacheMapMutex);
                return m_cacheMap[key];
            }

            BOOST_LOG_TRIVIAL(trace) << "getting secret (" << key << ") from key-vault";
            // get the key value from the key-vault.
            auto keyVal = m_secretsClient->GetSecret(key);


            // check if the value has a value (not null).
            if (keyVal.Value.Value.HasValue()) {
                string val = keyVal.Value.Value.Value();

                // acquire (lock) the mutex.
                LOCK_GUARD(m_cacheMapMutex);
                // set the cache value.
                return m_cacheMap[key] = val;
            } else {
                return "";
            }
        }

    }


    ConfigurationsComponent getConfigurationsComponent() {
        return fruit::createComponent()
                .registerProvider([]() {
                    BOOST_LOG_TRIVIAL(debug) << "creating azure key-vault secret client provider.";

                    auto credential = std::make_shared<Azure::Identity::ChainedTokenCredential>(
                            Azure::Identity::ChainedTokenCredential::Sources{
                                    make_shared<Azure::Identity::EnvironmentCredential>(),
                                    make_shared<Azure::Identity::ManagedIdentityCredential>()
                            }
                    );

                    BOOST_LOG_TRIVIAL(trace) << "receiving key-vault_url from env-vars.";
                    auto key_vault_url = std::getenv("AZURE_KEYVAULT_URL");
                    BOOST_LOG_TRIVIAL(trace) << "key-vault-url = " << key_vault_url;
                    auto client = new SecretClient(key_vault_url, credential);
                    return client;
                })
                .bind<Configurations, impl::ConfigurationsAzureImpl>();
    }
}
