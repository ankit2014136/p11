#include "clickshare_certificate_provider.h"


namespace clicksharecertificateprovider
{
ClickshareCertificateProvider::ClickshareCertificateProvider()
    : _cryptoProvider(createCryptoProvider("/usr/lib/softhsm/"))
{
}

bool ClickshareCertificateProvider::generatePrivateKeyPair(const std::string &algorithm, int keySize)
{
    return _cryptoProvider->generateKeyPair(algorithm, keySize);
}

bool ClickshareCertificateProvider::initSign(const std::string &label)
{
    return _cryptoProvider->initSign(label);
}

std::vector<uint8_t> ClickshareCertificateProvider::sign(const std::vector<std::uint8_t> &hash)
{
    return _cryptoProvider->sign(hash);
}

/* bool ClickshareCertificateProvider::getAttributes(const std::string &label, CK_ATTRIBUTE* attrs)
{
    return _cryptoProvider->getAttributes(label, attrs);
} */

std::vector<unsigned char> ClickshareCertificateProvider::readCertificate(const std::string &label) const
{
    return _cryptoProvider->readCertificate(label);
}
}  // namespace clicksharecertificateprovider