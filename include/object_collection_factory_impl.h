#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_FACTORY_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_FACTORY_IMPL_H

#include "object_collection_factory.h"

namespace clicksharecertificateprovider
{
class ObjectCollectionFactoryImpl : public ObjectCollectionFactory
{
public:
    ObjectCollectionFactoryImpl(std::shared_ptr<P11> p11,
                                std::shared_ptr<Pkcs11> pkcs11);

    std::unique_ptr<ObjectCollection> createObjectCollection(
        std::shared_ptr<LoginStateManager> loginStateManager,
        PKCS11_SLOT *slot,
        const std::string &userPin) const override;

private:
    std::shared_ptr<P11> _p11;
    std::shared_ptr<Pkcs11> _pkcs11;
};

} // namespace clicksharecertificateprovider

#endif // CLICKSHARE_CERTIFICATE_PROVIDER_OBJECT_COLLECTION_FACTORY_IMPL_H