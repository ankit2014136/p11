#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_MODULE_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_MODULE_H

#include <filesystem>
#include <memory>

#include "context.h"
#include "p11.h"
#include "pkcs11_wrapper.h"

namespace clicksharecertificateprovider
{

class Module
{
public:
    Module(std::shared_ptr<P11> p11, std::shared_ptr<Pkcs11> pkcs11, std::shared_ptr<Context> context, const std::filesystem::path &libraryPath);
    ~Module();

private:
    std::shared_ptr<P11> _p11;
    std::shared_ptr<Pkcs11> _pkcs11;
    std::shared_ptr<Context> _context;
};

}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_MODULE_H