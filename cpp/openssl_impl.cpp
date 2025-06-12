#include "openssl_impl.h"

namespace clicksharecertificateprovider
{

void OpenSSLImpl::ENGINE_free(ENGINE *engine)
{
    ::ENGINE_free(engine);
}

ENGINE *OpenSSLImpl::ENGINE_by_id(const char *id)
{
    return ::ENGINE_by_id(id);
}

int OpenSSLImpl::ENGINE_ctrl_cmd_string(ENGINE *e, const char *cmd_name, const char *arg, int cmd_optional)
{
    return ::ENGINE_ctrl_cmd_string(e, cmd_name, arg, cmd_optional);
}

int OpenSSLImpl::ENGINE_init(ENGINE *e)
{
    return ::ENGINE_init(e);
}

void OpenSSLImpl::ENGINE_load_builtin_engines()
{
    ::ENGINE_load_builtin_engines();
}

int OpenSSLImpl::ENGINE_set_default(ENGINE *e, unsigned int flags)
{
    return ::ENGINE_set_default(e, flags);
}
} // namespace clicksharecertificateprovider