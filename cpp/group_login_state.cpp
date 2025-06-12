#include "group_login_state.h"

#include "module.h"

namespace clicksharecertificateprovider {
GroupLoginState::GroupLoginState(std::shared_ptr<Env> environment)
    : LoginState(std::move(environment))
{
    const EnvironmentParameters& environmentParameters{
        {"CKTEEC_LOGIN_TYPE", "group"},
        {"CKTEEC_LOGIN_GID", "1026"}
    };
    setEnvironmentParameters(environmentParameters);
}

} // namespace clicksharecertificateprovider