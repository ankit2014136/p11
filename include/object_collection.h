#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_H

#include <string>
#include <vector>

#include "pkcs11_wrapper.h"

namespace clicksharecertificateprovider
{
class ObjectCollection
{
public:
    virtual ~ObjectCollection() = default;

    virtual bool writeData(const std::vector<std::uint8_t> &data, const std::string &label) = 0;
    virtual bool deleteObjectByLabel(CK_OBJECT_CLASS objectType, const std::string &label) = 0;
    virtual std::vector<std::uint8_t> readObjectByLabel(CK_OBJECT_CLASS objClass, const std::string &label) const = 0;
};

}  // namespace clicksharecertificateprovider

#endif // CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_H