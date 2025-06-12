#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_H

#include "env.h"

#include <map>
#include <string>
#include <memory>
#include <vector>

namespace clicksharecertificateprovider
{
using EnvironmentParameters = std::map<std::string, std::string>;

class LoginState
{
public:
    LoginState(std::shared_ptr<Env> environment);
    ~LoginState();
    bool operator==(const LoginState &other) const;
protected:
    void setEnvironmentParameters(const EnvironmentParameters &environmentParameters);
    void unsetEnvironmentVariables();

    std::shared_ptr<Env> _env;
    std::vector<std::string> _setEnvironmentVariables{};
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_LOGIN_STATE_H