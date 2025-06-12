#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_FACTORY_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_FACTORY_IMPL_H

#include "login_state_manager_factory.h"

namespace clicksharecertificateprovider
{
class LoginStateManagerFactoryImpl : public LoginStateManagerFactory
{
public:
    std::shared_ptr<LoginStateManager> createLoginStateManager(
        std::unique_ptr<LoginStateFactory> loginStateFactory,
        std::unique_ptr<ModuleFactory> moduleFactory,
        const UserType &userType) const override;
private:
    const std::filesystem::path _libraryDir;
};

} // namespace clicksharecertificateprovider

#endif // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_FACTORY_IMPL_H