#include "login_state_manager_factory_impl.h"

#include "login_state_manager_impl.h"

namespace clicksharecertificateprovider
{
std::shared_ptr<LoginStateManager> LoginStateManagerFactoryImpl::createLoginStateManager(
    std::unique_ptr<LoginStateFactory> loginStateFactory,
    std::unique_ptr<ModuleFactory> moduleFactory,
    const UserType &userType) const
{
    return std::make_shared<LoginStateManagerImpl>(
        std::move(loginStateFactory),
        std::move(moduleFactory),
        userType);
}

} // namespace clicksharecertificateprovider