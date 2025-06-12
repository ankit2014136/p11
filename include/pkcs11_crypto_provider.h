#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_PKCS11_CRYPTO_PROVIDER_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_PKCS11_CRYPTO_PROVIDER_H

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "context.h"
#include "engine.h"
#include "module.h"
#include "openssl.h"
#include "object_collection_factory.h"
#include "p11.h"
#include "pkcs11_wrapper.h"
#include "slots.h"
#include "user_type.h"
#include "sign.h"
#include "login_state_factory.h"
#include "login_state_manager_factory.h"

namespace clicksharecertificateprovider
{
class PKCS11CryptoProvider
{
public:
    PKCS11CryptoProvider(
        std::unique_ptr<LoginStateFactory> loginStateFactory,
        std::unique_ptr<LoginStateManagerFactory> loginStateManagerFactory,
        const std::filesystem::path &libraryDir,
        std::shared_ptr<P11> p11,
        std::shared_ptr<Pkcs11> pkcs11,
        std::shared_ptr<OpenSSL> openssl,
        std::shared_ptr<Engine> engine,
        std::unique_ptr<ObjectCollectionFactory> objectCollectionFactory);
    bool generateKeyPair(const std::string &algorithm, int keySize);
    bool initSign(const std::string &label);
    //bool getAttributes(const std::string &label, CK_ATTRIBUTE* attrs);
    std::vector<uint8_t> sign(const std::vector<std::uint8_t> &msg);
    std::vector<unsigned char> readCertificate(const std::string &label);

private:
    void initToken();
    bool initPin(const std::string &pin);

    const std::filesystem::path _libraryDir;
    std::shared_ptr<P11> _p11;
    std::shared_ptr<Pkcs11> _pkcs11;
    std::shared_ptr<OpenSSL> _openssl;
    std::shared_ptr<Engine> _engine;
    std::shared_ptr<Context> _context;
    std::shared_ptr<LoginStateManager> _loginStateManager;
    std::unique_ptr<ObjectCollectionFactory> _objectCollectionFactory;
    //std::unique_ptr<Module> _module;
    Slots _slots;
};
}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_PKCS11_CRYPTO_PROVIDER_H