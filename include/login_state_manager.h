#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_H

#include "user_type.h"

namespace clicksharecertificateprovider
{

class LoginStateManager
{
public:
    virtual ~LoginStateManager() = default;
    virtual void changeLoginState(const UserType &userType) = 0;
};
} // namespace clicksharecertificateprovider
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_MANAGER_H