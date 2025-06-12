#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_P11IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_P11IMPL_H

#include <memory>

#include "p11.h"

namespace clicksharecertificateprovider
{

class P11Impl : public P11
{
public:
    void PKCS11_CTX_free(PKCS11_CTX *ctx) override;
    int PKCS11_CTX_load(PKCS11_CTX *ctx, const char *module) override;
    void PKCS11_CTX_unload(PKCS11_CTX *ctx) override;
    PKCS11_CTX *PKCS11_CTX_new() override;
    int PKCS11_enumerate_slots(PKCS11_CTX *ctx, PKCS11_SLOT **slotsp, unsigned int *nslotsp) override;
    unsigned long PKCS11_get_slotid_from_slot(PKCS11_SLOT *slot) override;
    int PKCS11_init_token(PKCS11_TOKEN *token, const char *pin, const char *label) override;
    int PKCS11_init_pin(PKCS11_TOKEN *token, const char *pin) override;
    void PKCS11_release_all_slots(PKCS11_CTX *ctx, PKCS11_SLOT *slots, unsigned int nslots) override;
    int PKCS11_is_logged_in(PKCS11_SLOT *slot, int so, int *isLoggedIn) override;
    int PKCS11_login(PKCS11_SLOT *slot, int so, const char *pin) override;
    int PKCS11_logout(PKCS11_SLOT *slot) override;
};

}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_P11IMPL_H