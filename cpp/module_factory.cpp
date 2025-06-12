#include "module_factory.h"

namespace clicksharecertificateprovider
{

ModuleFactory::ModuleFactory(const std::filesystem::path &libraryDir, std::shared_ptr<P11> p11, std::shared_ptr<Pkcs11> pkcs11, std::shared_ptr<Context> context)
    : _libraryDir(libraryDir)
    , _p11(std::move(p11))
    , _pkcs11(std::move(pkcs11))
    , _context(std::move(context))
{
}

std::unique_ptr<Module> ModuleFactory::createModule() const
{
    return std::make_unique<Module>(_p11, _pkcs11, _context, _libraryDir / "libsofthsm2.so");
}
}  // namespace clicksharecertificateprovider