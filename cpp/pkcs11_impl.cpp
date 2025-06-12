#include "pkcs11_impl.h"

namespace clicksharecertificateprovider
{
CK_RV Pkcs11Impl::C_OpenSession(CK_SLOT_ID slotID, CK_FLAGS flags,
                                CK_VOID_PTR application, CK_NOTIFY notify,
                                CK_SESSION_HANDLE_PTR session)
{
    return ::C_OpenSession(slotID, flags, application, notify, session);
}

CK_RV Pkcs11Impl::C_CloseSession(CK_SESSION_HANDLE session)
{
    return ::C_CloseSession(session);
}

CK_RV Pkcs11Impl::C_CreateObject(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount, CK_OBJECT_HANDLE_PTR phObject)
{
    return ::C_CreateObject(hSession, pTemplate, ulCount, phObject);
}

CK_RV Pkcs11Impl::C_DestroyObject(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject)
{
    return ::C_DestroyObject(hSession, hObject);
}

CK_RV Pkcs11Impl::C_FindObjectsInit(CK_SESSION_HANDLE hSession, CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount)
{
    return ::C_FindObjectsInit(hSession, pTemplate, ulCount);
}

CK_RV Pkcs11Impl::C_FindObjects(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE_PTR phObject, CK_ULONG ulMaxObjectCount,
                                CK_ULONG_PTR pulObjectCount)
{
    return ::C_FindObjects(hSession, phObject, ulMaxObjectCount, pulObjectCount);
}

CK_RV Pkcs11Impl::C_FindObjectsFinal(CK_SESSION_HANDLE hSession)
{
    return ::C_FindObjectsFinal(hSession);
}

CK_RV Pkcs11Impl::C_GenerateKeyPair(CK_SESSION_HANDLE session, CK_MECHANISM_PTR mechanism,
                                    CK_ATTRIBUTE_PTR publicKeyTemplate, CK_ULONG publicKeyAttributeCount,
                                    CK_ATTRIBUTE_PTR privateKeyTemplate, CK_ULONG privateKeyAttributeCount,
                                    CK_OBJECT_HANDLE_PTR publicKey, CK_OBJECT_HANDLE_PTR privateKey)
{
    return ::C_GenerateKeyPair(session, mechanism, publicKeyTemplate, publicKeyAttributeCount,
                               privateKeyTemplate, privateKeyAttributeCount, publicKey, privateKey);
}

CK_RV Pkcs11Impl::C_Login(CK_SESSION_HANDLE session, CK_USER_TYPE userType, CK_UTF8CHAR_PTR pin, CK_ULONG pinLength)
{
    return ::C_Login(session, userType, pin, pinLength);
}

CK_RV Pkcs11Impl::C_Logout(CK_SESSION_HANDLE session)
{
    return ::C_Logout(session);
}

CK_RV Pkcs11Impl::C_Initialize(CK_VOID_PTR pInitArgs)
{
    return ::C_Initialize(pInitArgs);
}

CK_RV Pkcs11Impl::C_Finalize(CK_VOID_PTR pReserved)
{
    return ::C_Finalize(pReserved);
}

CK_RV Pkcs11Impl::C_CloseAllSessions(CK_SLOT_ID slotID)
{
    return ::C_CloseAllSessions(slotID);
}

CK_RV Pkcs11Impl::C_GetAttributeValue(CK_SESSION_HANDLE hSession, CK_OBJECT_HANDLE hObject,
                                      CK_ATTRIBUTE_PTR pTemplate, CK_ULONG ulCount)
{
    return ::C_GetAttributeValue(hSession, hObject, pTemplate, ulCount);
}

CK_RV Pkcs11Impl::C_SignInit(CK_SESSION_HANDLE session, CK_MECHANISM_PTR mechanism, CK_OBJECT_HANDLE privateKey)
{
    return ::C_SignInit(session, mechanism, privateKey);
}

CK_RV Pkcs11Impl::C_Sign(CK_SESSION_HANDLE session,  CK_UTF8CHAR_PTR data, CK_ULONG data_len,
        CK_UTF8CHAR_PTR signature, CK_ULONG_PTR signature_len)
{
    return ::C_Sign(session, data, data_len, signature, signature_len);
}

}  // namespace clicksharecertificateprovider