#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_INVALID_INPUT_EXCEPTION_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_INVALID_INPUT_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace clicksharecertificateprovider
{
class InvalidInputException : public std::logic_error
{
public:
    explicit InvalidInputException(const std::string &message)
        : std::logic_error("Invalid input: " + message)
    {
    }
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_EXCEPTIONS_INVALID_INPUT_EXCEPTION_H