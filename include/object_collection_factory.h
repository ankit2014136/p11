#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_FACTORY_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_FACTORY_H

#include <memory>

#include "login_state_manager.h"
#include "object_collection.h"
#include "slot.h"


namespace clicksharecertificateprovider
{
class ObjectCollectionFactory
{
public:
    virtual ~ObjectCollectionFactory() = default;
    virtual std::unique_ptr<ObjectCollection> createObjectCollection(
        std::shared_ptr<LoginStateManager> loginStateManager,
        PKCS11_SLOT *slot,
        const std::string &userPin) const = 0;
};

} // namespace clicksharecertificateprovider

#endif // CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_FACTORY_H