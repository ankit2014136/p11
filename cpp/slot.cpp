#include "slot.h"

#include "invalid_input_exception.h"
#include "login_exception.h"

namespace clicksharecertificateprovider
{
Slot::Slot(std::shared_ptr<P11> p11, PKCS11_SLOT *slot)
    : _p11(std::move(p11))
    , _slot(slot)
{
}

PKCS11_SLOT *Slot::getInternal()
{
    return _slot;
}

bool Slot::checkIfLoggedIn(const UserType userType)
{
    int isLoggedIn{0};
    const auto rc = _p11->PKCS11_is_logged_in(_slot, static_cast<int>(userType), &isLoggedIn);
    if (rc != 0) {
        throw LoginException("PKCS11_is_logged_in failed");
    }
    return isLoggedIn != 0;
}

bool Slot::login(const std::string &pin, const UserType userType)
{
    if (pin.empty()) {
        throw InvalidInputException("pin is empty");
    }

    if (checkIfLoggedIn(userType)) {
        return true;
    }

    const auto rc = _p11->PKCS11_login(_slot, static_cast<int>(userType), pin.c_str());
    if (rc != 0) {
        throw LoginException("PKCS11_login failed");
    }
    return true;
}

bool Slot::logout()
{
    const auto rc = _p11->PKCS11_logout(_slot);
    if (rc != 0) {
        throw LoginException("PKCS11_logout failed");
    }
    return true;
}

unsigned long Slot::getId() const
{
    if (!_slot) {
        throw std::runtime_error("Invalid slot pointer");
    }

    return _p11->PKCS11_get_slotid_from_slot(_slot);
}

bool Slot::isUserPinSet() const
{
    return _slot->token->userPinSet;
}
}  // namespace clicksharecertificateprovider