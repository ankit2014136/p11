#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_IMPL_H

#include <memory>

#include "login_state.h"
#include "login_state_factory.h"
#include "login_state_manager.h"
#include "module_factory.h"

namespace clicksharecertificateprovider
{

class LoginStateManagerImpl : public LoginStateManager
{
public:
    LoginStateManagerImpl(std::unique_ptr<LoginStateFactory> loginStateFactory, std::unique_ptr<ModuleFactory> moduleFactory, const UserType &initialUserType);
    void changeLoginState(const UserType &userType) override;

private:
    UserType _currentUser;
    std::unique_ptr<LoginStateFactory> _loginStateFactory;
    std::shared_ptr<LoginState> _loginState;
    std::unique_ptr<ModuleFactory> _moduleFactory;
    std::unique_ptr<Module> _module;
};
} // namespace clicksharecertificateprovider
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_IMPL_H