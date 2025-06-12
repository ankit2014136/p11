#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_PKCS11_IMPL_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_PKCS11_IMPL_H

#include "pkcs11_wrapper.h"

namespace clicksharecertificateprovider
{
class Pkcs11Impl : public Pkcs11
{
public:
    CK_RV C_OpenSession(CK_SLOT_ID slotID, CK_FLAGS flags,
                        CK_VOID_PTR application, CK_NOTIFY notify,
                        CK_SESSION_HANDLE_PTR session) override;
    CK_RV C_CloseSession(CK_SESSION_HANDLE session) override;
    CK_RV C_CreateObject(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate,
                         CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phObject) override;
    CK_RV C_DestroyObject(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject) override;
    CK_RV C_FindObjectsInit(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount) override;
    CK_RV C_FindObjects(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount,
                        CK_ULONG_PTR pulObjectCount) override;
    CK_RV C_FindObjectsFinal(CK_SESSION_HANDLE hSession) override;
    CK_RV C_GenerateKeyPair(CK_SESSION_HANDLE session, CK_MECHANISM_PTR mechanism,
                            CK_ATTRIBUTE_PTR publicKeyTemplate, CK_ULONG publicKeyAttributeCount,
                            CK_ATTRIBUTE_PTR privateKeyTemplate, CK_ULONG privateKeyAttributeCount,
                            CK_OBJECT_HANDLE_PTR publicKey, CK_OBJECT_HANDLE_PTR privateKey) override;
    CK_RV C_Login(CK_SESSION_HANDLE session, CK_USER_TYPE userType, CK_UTF8CHAR_PTR pin, CK_ULONG pinLength) override;
    CK_RV C_Logout(CK_SESSION_HANDLE session) override;
    CK_RV C_Initialize(CK_VOID_PTR pInitArgs) override;
    CK_RV C_Finalize(CK_VOID_PTR pReserved) override;
    CK_RV C_CloseAllSessions(CK_SLOT_ID slotID) override;
    CK_RV C_GetAttributeValue(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject,
                                      CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount) override;
    CK_RV C_SignInit(CK_SESSION_HANDLE session, CK_MECHANISM_PTR mechanism, CK_OBJECT_HANDLE privateKey) override;
    CK_RV C_Sign(CK_SESSION_HANDLE session,  CK_UTF8CHAR_PTR data, CK_ULONG data_len,
            CK_UTF8CHAR_PTR signature, CK_ULONG_PTR signature_len) override;

};
}  //namespace clicksharecertificateprovider

#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_PKCS11_IMPL_H