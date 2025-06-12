#include "env_impl.h"

#include <cstdlib>

namespace clicksharecertificateprovider
{
int EnvImpl::setenv(const char *name, const char *value, int overwrite)
{
    return ::setenv(name, value, overwrite);
}

int EnvImpl::unsetenv(const char *name)
{
    return ::unsetenv(name);
}

}  // namespace clicksharecertificateprovider