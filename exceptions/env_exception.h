#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_ENV_EXCEPTION_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_ENV_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace clicksharecertificateprovider
{
class EnvException : public std::runtime_error
{
public:
    explicit EnvException(const std::string &message)
        : std::runtime_error("Env error: " + message)
    {
    }
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_ENV_EXCEPTION_H