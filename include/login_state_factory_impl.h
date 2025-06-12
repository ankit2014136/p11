#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_CONCRETE_LOGIN_STATE_FACTORY_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_CONCRETE_LOGIN_STATE_FACTORY_IMPL_H

#include "login_state_factory.h"

namespace clicksharecertificateprovider
{

class LoginStateFactoryImpl : public LoginStateFactory
{
public:
    LoginStateFactoryImpl(std::shared_ptr<Env> environment);
    std::shared_ptr<LoginState> createLoginState(const UserType &userType) const override;
private:
    std::shared_ptr<Env> _environment;
};

}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_CONCRETE_LOGIN_STATE_FACTORY_IMPL_H