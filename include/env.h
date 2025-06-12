#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_ENV_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_ENV_H

namespace clicksharecertificateprovider
{
class Env
{
public:
    virtual ~Env() = default;
    virtual int setenv(const char *name, const char *value, int overwrite) = 0;
    virtual int unsetenv(const char *name) = 0;
};
} // namespace clicksharecertificateprovider
#endif // CLICKSHARE_CERTIFICATE_PROVIDER_ENV_H