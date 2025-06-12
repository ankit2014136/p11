#include "user_login_state.h"

#include "module.h"

namespace clicksharecertificateprovider {

UserLoginState::UserLoginState(std::shared_ptr<Env> environment)
    : LoginState(std::move(environment))
{
    const EnvironmentParameters environmentParameters{
        {"CKTEEC_LOGIN_TYPE", "user"},
    };
    setEnvironmentParameters(environmentParameters);
}

}  // namespace clicksharecertificateprovider