#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_ENV_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_ENV_IMPL_H

#include "env.h"

namespace clicksharecertificateprovider
{
class EnvImpl : public Env
{
public:
    int setenv(const char *name, const char *value, int overwrite) override;
    int unsetenv(const char *name) override;
};
} // namespace clicksharecertificateprovider
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_ENV_IMPL_H