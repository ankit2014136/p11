#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_OPENSSL_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_OPENSSL_IMPL_H

#include "openssl.h"

namespace clicksharecertificateprovider
{
class OpenSSLImpl : public OpenSSL
{
public:
    void ENGINE_free(ENGINE *engine) override;
    ENGINE *ENGINE_by_id(const char *id) override;
    int ENGINE_ctrl_cmd_string(ENGINE *e, const char *cmd_name, const char *arg, int cmd_optional) override;
    int ENGINE_init(ENGINE *e) override;
    void ENGINE_load_builtin_engines() override;
    int ENGINE_set_default(ENGINE *e, unsigned int flags) override;

};
}
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_OPENSSL_H