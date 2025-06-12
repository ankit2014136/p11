#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_MODULE_FACTORY_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_MODULE_FACTORY_H

#include "module.h"

#include <string>
#include <memory>

namespace clicksharecertificateprovider
{
class ModuleFactory
{
public:
    ModuleFactory(const std::filesystem::path &libraryDir, std::shared_ptr<P11> p11, std::shared_ptr<Pkcs11> pkcs11, std::shared_ptr<Context> context);
    ~ModuleFactory() = default;
    std::unique_ptr<Module> createModule() const;
private:
    const std::filesystem::path _libraryDir;
    std::shared_ptr<P11> _p11;
    std::shared_ptr<Pkcs11> _pkcs11;
    std::shared_ptr<Context> _context;
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_MODULE_FACTORY_H