#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_LOGIN_EXCEPTION_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_LOGIN_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace clicksharecertificateprovider
{
class LoginException : public std::runtime_error
{
public:
    explicit LoginException(const std::string &message)
        : std::runtime_error("Login error: " + message)
    {
    }
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_LOGIN_EXCEPTION_H