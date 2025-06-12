#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_KEY_PAIR_GENERATOR_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_KEY_PAIR_GENERATOR_H

#include <memory>
#include <string>

#include "pkcs11_wrapper.h"
#include "session.h"

namespace clicksharecertificateprovider
{
class KeyPairGenerator
{
public:
    KeyPairGenerator(long unsigned int slotId, std::string pin, std::shared_ptr<LoginStateManager> loginStateManager, std::shared_ptr<Pkcs11> pkcs11);
    void generateKeyPairWithECPrime256Curve();

private:
    std::shared_ptr<Pkcs11> _pkcs11;
    Session _session;
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_KEY_PAIR_GENERATOR_H