#include "slots.h"
#include <stdexcept>
#include <string.h>

namespace clicksharecertificateprovider
{
Slots::Slots(std::shared_ptr<P11> p11, std::shared_ptr<Context> context)
    : _p11(std::move(p11))
    , _ctx(std::move(context))
    , _numberOfSlots(0)
    , _slots(nullptr, PKCS11_SLOTS_DELETER{_p11.get(), _ctx.get(), _numberOfSlots})
{
    PKCS11_SLOT *slots{};
    if (_p11->PKCS11_enumerate_slots(_ctx->getInternal(), &slots, &_numberOfSlots) != 0) {
        throw std::runtime_error("Failed to enumerate slots");
    }
    _slots.reset(slots);
}

PKCS11_SLOT *Slots::getAvailableSlot(const std::string &label) const
{
    PKCS11_SLOT *firstAvailableSlot{};
    for (unsigned int i = 0; i < _numberOfSlots; ++i) {
        PKCS11_SLOT *slot = &_slots.get()[i];
        if (slot->token) {
            if (strcmp(slot->token->label, label.c_str()) == 0) {
                return slot;
            }
            if (!firstAvailableSlot && !slot->token->initialized) {
                firstAvailableSlot = slot;
            }
        }
    }
    if (!firstAvailableSlot) {
        throw std::runtime_error("No available slot found");
    }
    return firstAvailableSlot;
}
}  // namespace clicksharecertificateprovider