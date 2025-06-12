#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_CLICKSHARE_CERTIFICATE_PROVIDER_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_CLICKSHARE_CERTIFICATE_PROVIDER_H

#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "crypto_provider_factory.h"

namespace clicksharecertificateprovider
{
class ClickshareCertificateProvider
{
public:
    ClickshareCertificateProvider();
    bool generatePrivateKeyPair(const std::string &algorithm, int keySize);
    bool initSign(const std::string &label);
    //bool getAttributes(const std::string &label, CK_ATTRIBUTE* attrs);
    std::vector<uint8_t> sign(const std::vector<std::uint8_t> &msg);
    std::vector<unsigned char> readCertificate(const std::string &label) const;

private:
    std::shared_ptr<PKCS11CryptoProvider> _cryptoProvider;
};
}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_CLICKSHARE_CERTIFICATE_PROVIDER_H