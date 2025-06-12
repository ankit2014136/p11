#include "crypto_provider_factory.h"

#include "env_impl.h"
#include "login_state_factory_impl.h"
#include "login_state_manager_factory_impl.h"
#include "module_factory.h"
#include "object_collection_factory_impl.h"
#include "openssl_impl.h"
#include "p11_impl.h"
#include "pkcs11_crypto_provider.h"
#include "pkcs11_impl.h"

namespace clicksharecertificateprovider
{

namespace
{
std::shared_ptr<OpenSSL> openSSL()
{
    static auto instance{std::make_shared<OpenSSLImpl>()};
    return instance;
}

// ensure only a single instance of engine is created due to unknow issues with engine_free on android
std::shared_ptr<Engine> engine(const std::filesystem::path &libraryDir)
{
    static auto instance{std::make_shared<Engine>(openSSL(), libraryDir)};
    return instance;
}
} // namespace

std::shared_ptr<PKCS11CryptoProvider> createCryptoProvider(const std::filesystem::path &libraryDir)
{
    auto p11Impl = std::make_shared<P11Impl>();
    auto pkcs11Impl = std::make_shared<Pkcs11Impl>();
    static auto instance{std::make_shared<PKCS11CryptoProvider>(
        std::make_unique<LoginStateFactoryImpl>(std::make_shared<EnvImpl>()),
        std::make_unique<LoginStateManagerFactoryImpl>(),
        libraryDir,
        p11Impl,
        pkcs11Impl,
        openSSL(),
        engine(libraryDir),
        std::make_unique<ObjectCollectionFactoryImpl>(p11Impl, pkcs11Impl))};
    return instance;
} 
} // namespace clicksharecertificateprovider