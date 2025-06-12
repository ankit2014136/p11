#include "login_state.h"

#include "module.h"
#include "env_exception.h"

namespace clicksharecertificateprovider
{
LoginState::LoginState(std::shared_ptr<Env> environment)
    : _env(std::move(environment))
{
}

LoginState::~LoginState()
{
    unsetEnvironmentVariables();
}

void LoginState::setEnvironmentParameters(const EnvironmentParameters &environmentParameters)
{
    for (const auto &variable : environmentParameters)
    {
        _setEnvironmentVariables.push_back(variable.first);
        if (_env->setenv(variable.first.c_str(), variable.second.c_str(), 1) != 0)
        {
            throw EnvException("Failed to set environment variable");
        }
    }
}

void LoginState::unsetEnvironmentVariables()
{
    for (const auto &variable : _setEnvironmentVariables)
    {
        _env->unsetenv(variable.c_str());
    }
}

bool LoginState::operator==(const LoginState &other) const
{
    return _setEnvironmentVariables == other._setEnvironmentVariables;
}
} // namespace clicksharecertificateprovider