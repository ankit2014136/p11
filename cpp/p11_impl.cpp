#include "p11_impl.h"

namespace clicksharecertificateprovider
{
void P11Impl::PKCS11_CTX_free(PKCS11_CTX *ctx)
{
    ::PKCS11_CTX_free(ctx);
}

PKCS11_CTX *P11Impl::PKCS11_CTX_new()
{
    return ::PKCS11_CTX_new();
}

int P11Impl::PKCS11_CTX_load(PKCS11_CTX *ctx, const char *module)
{
    return ::PKCS11_CTX_load(ctx, module);
}

void P11Impl::PKCS11_CTX_unload(PKCS11_CTX *ctx)
{
    ::PKCS11_CTX_unload(ctx);
}

int P11Impl::PKCS11_enumerate_slots(PKCS11_CTX *ctx, PKCS11_SLOT **slotsp, unsigned int *nslotsp)
{
    return ::PKCS11_enumerate_slots(ctx, slotsp, nslotsp);
}

unsigned long P11Impl::PKCS11_get_slotid_from_slot(PKCS11_SLOT *slot)
{
    return ::PKCS11_get_slotid_from_slot(slot);
}

int P11Impl::PKCS11_init_token(PKCS11_TOKEN *token, const char *pin, const char *label)
{
    return ::PKCS11_init_token(token, pin, label);
}

int P11Impl::PKCS11_init_pin(PKCS11_TOKEN *token, const char *pin)
{
    return ::PKCS11_init_pin(token, pin);
}

void P11Impl::PKCS11_release_all_slots(PKCS11_CTX *ctx, PKCS11_SLOT *slots, unsigned int nslots)
{
    ::PKCS11_release_all_slots(ctx, slots, nslots);
}

int P11Impl::PKCS11_is_logged_in(PKCS11_SLOT *slot, int so, int *isLoggedIn)
{
    return ::PKCS11_is_logged_in(slot, so, isLoggedIn);
}

int P11Impl::PKCS11_login(PKCS11_SLOT *slot, int so, const char *pin)
{
    return ::PKCS11_login(slot, so, pin);
}

int P11Impl::PKCS11_logout(PKCS11_SLOT *slot)
{
    return ::PKCS11_logout(slot);
}

}  // namespace clicksharecertificateprovider