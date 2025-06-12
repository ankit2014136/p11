#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_SLOTS_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_SLOTS_H

#include <memory>
#include <string>

#include <libp11.h>

#include "context.h"
#include "p11.h"

namespace clicksharecertificateprovider
{
class Slots
{
public:
    Slots(std::shared_ptr<P11> p11, std::shared_ptr<Context> context);
    PKCS11_SLOT *getAvailableSlot(const std::string &label) const;

private:
    struct PKCS11_SLOTS_DELETER {
        void operator()(PKCS11_SLOT *slots) const
        {
            if (slots) {
                _p11->PKCS11_release_all_slots(_ctx->getInternal(), slots, _numberOfSlots);
            }
        }
        P11 *_p11;
        Context *_ctx;
        unsigned int &_numberOfSlots;
    };
    std::shared_ptr<P11> _p11;
    std::shared_ptr<Context> _ctx;
    std::unique_ptr<PKCS11_SLOT, PKCS11_SLOTS_DELETER> _slots;
    unsigned int _numberOfSlots;
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_SLOTS_H