#include "login_state_manager_impl.h"

namespace clicksharecertificateprovider
{
LoginStateManagerImpl::LoginStateManagerImpl(std::unique_ptr<LoginStateFactory> loginStateFactory, std::unique_ptr<ModuleFactory> moduleFactory, const UserType &initialUserType)
    : _loginStateFactory(std::move(loginStateFactory))
    , _currentUser(initialUserType)
    , _loginState(_loginStateFactory->createLoginState(initialUserType))
    , _moduleFactory(std::move(moduleFactory))
    , _module(_moduleFactory->createModule())
{
}

void LoginStateManagerImpl::changeLoginState(const UserType &userType)
{
    if (_currentUser == userType)
    {
        return;
    }
    _loginState.reset();
    _module.reset();
    _loginState = _loginStateFactory->createLoginState(userType);
    _module = _moduleFactory->createModule();
    _currentUser = userType;
}
} // namespace clicksharecertificateprovider