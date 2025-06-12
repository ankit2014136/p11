#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_FACTORY_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_FACTORY_H

#include <memory>

#include "env.h"
#include "login_state.h"
#include "user_type.h"

namespace clicksharecertificateprovider
{

class LoginStateFactory
{
public:
    virtual ~LoginStateFactory() = default;
    virtual std::shared_ptr<LoginState> createLoginState(const UserType &userType) const = 0;
};

}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_FACTORY_H