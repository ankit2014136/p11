#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_SLOT_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_SLOT_H

#include <memory>
#include <string>

#include <libp11.h>

#include "p11.h"
#include "user_type.h"

namespace clicksharecertificateprovider
{
class Slot
{
public:
    Slot(std::shared_ptr<P11> p11, PKCS11_SLOT *slot);
    bool login(const std::string &pin, const UserType userType);
    bool logout();
    unsigned long getId() const;
    PKCS11_SLOT *getInternal();
    bool isUserPinSet() const;

private:
    bool checkIfLoggedIn(const UserType userType);
    PKCS11_SLOT *_slot{};
    std::shared_ptr<P11> _p11;
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_SLOT_H