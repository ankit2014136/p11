#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_CONTEXT_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_CONTEXT_H

#include <memory>

#include <libp11.h>

#include "p11.h"

namespace clicksharecertificateprovider
{
class Context
{
public:
    Context(std::shared_ptr<P11> p11);
    PKCS11_CTX *getInternal();

private:
    struct PKCS11_CTX_DELETER {
        P11 *_p11;
        void operator()(PKCS11_CTX *ctx) const
        {
            if (ctx) {
                _p11->PKCS11_CTX_free(ctx);
            }
        }
    };

    std::shared_ptr<P11> _p11;
    std::unique_ptr<PKCS11_CTX, PKCS11_CTX_DELETER> _ctx;
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_CONTEXT_H