#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_GROUP_LOGIN_STATE_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_GROUP_LOGIN_STATE_H

#include "login_state.h"

namespace clicksharecertificateprovider
{
class GroupLoginState : public LoginState
{
public:
    GroupLoginState(std::shared_ptr<Env> environment);
};
} // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_GROUP_LOGIN_STATE_H