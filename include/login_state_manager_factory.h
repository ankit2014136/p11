#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_FACTORY_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_FACTORY_H

#include <memory>

#include "login_state_factory.h"
#include "login_state_manager.h"
#include "module_factory.h"
#include "user_type.h"

namespace clicksharecertificateprovider
{

class LoginStateManagerFactory
{
public:
    virtual ~LoginStateManagerFactory() = default;
    virtual std::shared_ptr<LoginStateManager> createLoginStateManager(
        std::unique_ptr<LoginStateFactory> loginStateFactory,
        std::unique_ptr<ModuleFactory> moduleFactory,
        const UserType &userType) const = 0;
};

} // namespace clicksharecertificateprovider

#endif // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_FACTORY_H