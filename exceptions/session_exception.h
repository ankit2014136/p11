#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_SESSION_EXCEPTION_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_SESSION_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace clicksharecertificateprovider
{
class SessionException : public std::runtime_error
{
public:
    explicit SessionException(const std::string &message)
        : std::runtime_error("Session error: " + message)
    {
    }
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_SESSION_EXCEPTION_H