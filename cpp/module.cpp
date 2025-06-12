#include "module.h"

namespace clicksharecertificateprovider
{
Module::Module(std::shared_ptr<P11> p11,  std::shared_ptr<Pkcs11> pkcs11, std::shared_ptr<Context> context, const std::filesystem::path &libraryPath)
    : _p11(std::move(p11))
    , _pkcs11(std::move(pkcs11))
    , _context(std::move(context))
{
    if (_p11->PKCS11_CTX_load(_context->getInternal(), libraryPath.c_str()) != 0) {
        throw std::runtime_error("Failed to load " + libraryPath.filename().string() + " library");
    }

    _pkcs11->C_Initialize(nullptr);
}

Module::~Module()
{
    _p11->PKCS11_CTX_unload(_context->getInternal());
    _pkcs11->C_Finalize(nullptr);
}
}  // namespace clicksharecertificateprovider