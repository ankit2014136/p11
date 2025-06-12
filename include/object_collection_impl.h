#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_IMPL_H

#include <memory>
#include <vector>

#include "login_state_manager.h"
#include "object_collection.h"
#include "p11.h"
#include "session.h"
#include "slot.h"

namespace clicksharecertificateprovider
{

class ObjectCollectionImpl : public ObjectCollection
{
public:
    ObjectCollectionImpl(std::shared_ptr<P11> p11,
                     std::shared_ptr<Pkcs11> pkcs11,
                     std::shared_ptr<LoginStateManager> loginStateManager,
                     PKCS11_SLOT *slot,
                     const std::string &userPin);

    bool writeData(const std::vector<std::uint8_t> &data, const std::string &label) override;
    bool deleteObjectByLabel(CK_OBJECT_CLASS objectType, const std::string &label) override;
    std::vector<std::uint8_t> readObjectByLabel(CK_OBJECT_CLASS objClass, const std::string &label) const override;

private:
    std::shared_ptr<Pkcs11> _pkcs11;
    Session _session;
};

}  // namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_IMPL_H