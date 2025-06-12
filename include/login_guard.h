#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_GUARD_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_GUARD_H

#include <string>

#include "login_state_manager.h"
#include "slot.h"
#include "user_type.h"

namespace clicksharecertificateprovider
{
class LoginGuard
{
public:
    LoginGuard(std::shared_ptr<LoginStateManager> loginStateManager,
               Slot &slot,
               const std::string &pin,
               const UserType userType);
    ~LoginGuard();

private:
    bool login(const std::string &pin, const UserType userType);
    bool logout();

    Slot &_slot;
    std::shared_ptr<LoginStateManager> _loginStateManager;
};
}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_GUARD_H