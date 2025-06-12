#include "login_guard.h"

namespace clicksharecertificateprovider
{
LoginGuard::LoginGuard(std::shared_ptr<LoginStateManager> loginStateManager,
                       Slot &slot,
                       const std::string &pin,
                       const UserType userType)
    : _slot(slot)
    , _loginStateManager(loginStateManager)
{
    login(pin, userType);
}

LoginGuard::~LoginGuard()
{
    logout();
}

bool LoginGuard::login(const std::string &pin, const UserType userType)
{
    _loginStateManager->changeLoginState(userType);
    return _slot.login(pin, userType);
}

bool LoginGuard::logout()
{
    return _slot.logout();
}
}  // namespace clicksharecertificateprovider