#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_USER_REAL_LOGIN_STATE_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_USER_REAL_LOGIN_STATE_H

#include "login_state.h"

namespace clicksharecertificateprovider
{
class UserLoginState : public LoginState
{
public:
    UserLoginState(std::shared_ptr<Env> environment);
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_USER_REAL_LOGIN_STATE_H