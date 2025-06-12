#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_P11_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_P11_H

#include <libp11.h>

namespace clicksharecertificateprovider
{
class P11
{
public:
    virtual ~P11() = default;
    virtual void PKCS11_CTX_free(PKCS11_CTX *ctx) = 0;
    virtual int PKCS11_CTX_load(PKCS11_CTX *ctx, const char *module) = 0;
    virtual void PKCS11_CTX_unload(PKCS11_CTX *ctx) = 0;
    virtual PKCS11_CTX *PKCS11_CTX_new() = 0;
    virtual unsigned long PKCS11_get_slotid_from_slot(PKCS11_SLOT *slot) = 0;
    virtual int PKCS11_init_token(PKCS11_TOKEN *token, const char *pin, const char *label) = 0;
    virtual int PKCS11_init_pin(PKCS11_TOKEN *token, const char *pin) = 0;
    virtual int PKCS11_enumerate_slots(PKCS11_CTX *ctx, PKCS11_SLOT **slotsp, unsigned int *nslotsp) = 0;
    virtual void PKCS11_release_all_slots(PKCS11_CTX *ctx, PKCS11_SLOT *slots, unsigned int nslots) = 0;
    virtual int PKCS11_is_logged_in(PKCS11_SLOT *slot, int so, int *isLoggedIn) = 0;
    virtual int PKCS11_login(PKCS11_SLOT *slot, int so, const char *pin) = 0;
    virtual int PKCS11_logout(PKCS11_SLOT *slot) = 0;
};
}  //namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_P11_H