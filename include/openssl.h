#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_OPENSSL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_OPENSSL_H

#include <openssl/engine.h>

namespace clicksharecertificateprovider
{
class OpenSSL
{
public:
    virtual ~OpenSSL() = default;
    virtual void ENGINE_free(ENGINE *engine) = 0;
    virtual ENGINE *ENGINE_by_id(const char *id) = 0;
    virtual int ENGINE_ctrl_cmd_string(ENGINE *e, const char *cmd_name, const char *arg, int cmd_optional) = 0;
    virtual int ENGINE_init(ENGINE *e) = 0;
    virtual void ENGINE_load_builtin_engines() = 0;
    virtual int ENGINE_set_default(ENGINE *e, unsigned int flags) = 0;
};
}
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_OPENSSL_H