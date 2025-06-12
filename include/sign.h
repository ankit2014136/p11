#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_SIGN_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_SIGN_H

#include <memory>
#include <vector>
#include <string>

#include "pkcs11_wrapper.h"
#include "session.h"

namespace clicksharecertificateprovider
{
class Sign
{
public:
    Sign(long unsigned int slotId, std::string pin, std::shared_ptr<LoginStateManager> loginStateManager, std::shared_ptr<Pkcs11> pkcs11);
    std::vector<uint8_t> signData(const std::vector<std::uint8_t> &msg);
    bool initSign(const std::string &label);
    //bool getAttributes(const std::string &label, CK_ATTRIBUTE* attrs);

private:
    std::shared_ptr<Pkcs11> _pkcs11;
    Session _session;
    CK_OBJECT_HANDLE privateKey;
    void getPrivateKeyHandle(const std::string &label);
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_SIGN_H