#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_ENGINE_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_ENGINE_H

#include <filesystem>
#include <memory>
#include <string>

#include <openssl/engine.h>

#include "openssl.h"

namespace clicksharecertificateprovider
{

class Engine
{
public:
    using ENGINE_PTR = std::shared_ptr<ENGINE>;
    Engine(std::shared_ptr<OpenSSL> openssl, const std::filesystem::path &libraryPath);
    ENGINE *get() { return _engine.get(); }
private:
    ENGINE_PTR initializeEngine(const std::filesystem::path &libraryPath);

    std::shared_ptr<OpenSSL> _openssl;
    ENGINE_PTR _engine;
    
};

} // namespace clicksharecertificateprovider
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_ENGINE_H