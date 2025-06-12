#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_CRYPTO_PROVIDER_FACTORY_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_CRYPTO_PROVIDER_FACTORY_H

#include <filesystem>
#include <memory>
#include <string>

#include "pkcs11_crypto_provider.h"

namespace clicksharecertificateprovider
{

std::shared_ptr<PKCS11CryptoProvider> createCryptoProvider(const std::filesystem::path &libraryDir);

}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_CRYPTO_PROVIDER_FACTORY_H