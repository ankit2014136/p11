#include "context.h"

#include <stdexcept>

namespace clicksharecertificateprovider
{
Context::Context(std::shared_ptr<P11> p11)
    : _p11(p11)
    , _ctx(_p11->PKCS11_CTX_new(), PKCS11_CTX_DELETER{_p11.get()})

{
    if (!_ctx) {
        throw std::runtime_error("Failed to create PKCS11 context");
    }
}

PKCS11_CTX *Context::getInternal()
{
    return _ctx.get();
}
}  // namespace clicksharecertificateprovider