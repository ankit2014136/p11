#include "object_collection_impl.h"

#include <stdexcept>

namespace
{

class ObjectsFinder
{
public:
    ObjectsFinder(std::shared_ptr<clicksharecertificateprovider::Pkcs11> pkcs11,
                  CK_SESSION_HANDLE session,
                  CK_ATTRIBUTE *searchTemplate,
                  CK_ULONG templateCount)
        : _pkcs11(std::move(pkcs11))
        , _session(session)
        , _initialized(false)
    {
        CK_RV rv = _pkcs11->C_FindObjectsInit(_session, searchTemplate, templateCount);
        if (rv != CKR_OK) {
            throw std::runtime_error("Failed to initialize object finding");
        }
        _initialized = true;
    }

    ~ObjectsFinder()
    {
        if (_initialized) {
            _pkcs11->C_FindObjectsFinal(_session);
        }
    }

    CK_OBJECT_HANDLE getNextObject()
    {
        CK_OBJECT_HANDLE objectHandle = CK_INVALID_HANDLE;
        CK_ULONG foundCount = 0;
        CK_RV rv = _pkcs11->C_FindObjects(_session, &objectHandle, 1, &foundCount);
        if (rv != CKR_OK) {
            throw std::runtime_error("Failed to find objects");
        }
        return (foundCount == 0) ? CK_INVALID_HANDLE : objectHandle;
    }

private:
    std::shared_ptr<clicksharecertificateprovider::Pkcs11> _pkcs11;
    CK_SESSION_HANDLE _session;
    bool _initialized;
};

}  // unnamed namespace

namespace clicksharecertificateprovider
{

ObjectCollectionImpl::ObjectCollectionImpl(std::shared_ptr<P11> p11,
                                   std::shared_ptr<Pkcs11> pkcs11,
                                   std::shared_ptr<LoginStateManager> loginStateManager,
                                   PKCS11_SLOT *slot,
                                   const std::string &userPin)
    : _pkcs11(std::move(pkcs11))
    , _session(p11->PKCS11_get_slotid_from_slot(slot), userPin, loginStateManager, _pkcs11)
{
}

bool ObjectCollectionImpl::writeData(const std::vector<std::uint8_t> &data, const std::string &label)
{
    if (data.empty()) {
        return false;
    }

    CK_OBJECT_CLASS objClass = CKO_DATA;

    deleteObjectByLabel(objClass, label);

    CK_BBOOL tokenFlag = CK_TRUE;
    std::vector<CK_ATTRIBUTE> attributes{
        {CKA_CLASS, &objClass, sizeof(objClass)},
        {CKA_TOKEN, &tokenFlag, sizeof(tokenFlag)},
        {CKA_LABEL, const_cast<char *>(label.c_str()), static_cast<CK_ULONG>(label.size())},
        {CKA_VALUE, const_cast<std::uint8_t *>(data.data()), static_cast<CK_ULONG>(data.size())}};

    CK_OBJECT_HANDLE objectHandle;
    CK_RV rv = _pkcs11->C_CreateObject(_session.getSession(),
                                       attributes.data(),
                                       static_cast<CK_ULONG>(attributes.size()),
                                       &objectHandle);
    return rv == CKR_OK;
}

bool ObjectCollectionImpl::deleteObjectByLabel(CK_OBJECT_CLASS objectType, const std::string &label)
{
    CK_ATTRIBUTE searchTemplate[] = {
        {CKA_CLASS, &objectType, sizeof(objectType)},
        {CKA_LABEL, const_cast<char *>(label.c_str()), static_cast<CK_ULONG>(label.size())}};

    ObjectsFinder finder(_pkcs11, _session.getSession(), searchTemplate, 2);

    while (true) {
        CK_OBJECT_HANDLE objectHandle = finder.getNextObject();
        if (objectHandle == CK_INVALID_HANDLE) {
            break;
        }
        CK_RV rv = _pkcs11->C_DestroyObject(_session.getSession(), objectHandle);
        if (rv != CKR_OK) {
            throw std::runtime_error("Failed to destroy existing object");
        }
    }

    return true;
}

std::vector<std::uint8_t> ObjectCollectionImpl::readObjectByLabel(CK_OBJECT_CLASS objClass, const std::string &label) const
{
    std::vector<unsigned char> objectContent;

    CK_ATTRIBUTE searchTemplate[] = {
        {CKA_CLASS, &objClass, sizeof(objClass)},
        {CKA_LABEL, const_cast<char *>(label.c_str()), static_cast<CK_ULONG>(label.size())}};

    ObjectsFinder finder(_pkcs11, _session.getSession(), searchTemplate, 2);

    CK_OBJECT_HANDLE objectHandle = finder.getNextObject();

    if (objectHandle == CK_INVALID_HANDLE) {
        return std::vector<std::uint8_t>();
    }

    CK_ATTRIBUTE valueAttr = { CKA_VALUE, nullptr, 0 };
    CK_RV rv = _pkcs11->C_GetAttributeValue(_session.getSession(), objectHandle, &valueAttr, 1);
    if (rv != CKR_OK) {
        throw std::runtime_error("Failed to get object value size");
    }

    objectContent.resize(valueAttr.ulValueLen);
    valueAttr.pValue = objectContent.data();

    rv = _pkcs11->C_GetAttributeValue(_session.getSession(), objectHandle, &valueAttr, 1);
    if (rv != CKR_OK) {
        throw std::runtime_error("Failed to get object value");
    }

    return objectContent;
}

}  // namespace clicksharecertificateprovider