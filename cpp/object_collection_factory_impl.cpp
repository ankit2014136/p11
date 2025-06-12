#include "object_collection_factory_impl.h"

#include "object_collection_impl.h"

namespace clicksharecertificateprovider
{
ObjectCollectionFactoryImpl::ObjectCollectionFactoryImpl(std::shared_ptr<P11> p11,
                                                         std::shared_ptr<Pkcs11> pkcs11)
    : _p11(std::move(p11))
    , _pkcs11(std::move(pkcs11))
{
}

std::unique_ptr<ObjectCollection> ObjectCollectionFactoryImpl::createObjectCollection(
    std::shared_ptr<LoginStateManager> loginStateManager,
    PKCS11_SLOT *slot,
    const std::string &userPin) const
{
    return std::make_unique<ObjectCollectionImpl>(_p11, _pkcs11, loginStateManager, slot, userPin);
}

} // namespace clicksharecertificateprovider