#include "sign.h"

#include <stdexcept>
#include<iostream>
#include<cstring>
#include <openssl/sha.h> // For SHA-512

namespace clicksharecertificateprovider
{
Sign::Sign(long unsigned int slotId, std::string pin, std::shared_ptr<LoginStateManager> loginStateManager, std::shared_ptr<Pkcs11> pkcs11)
    : _pkcs11(pkcs11)
    , _session(slotId, std::move(pin), loginStateManager, pkcs11)
{
}

bool Sign::initSign(const std::string &label){
    std::cout << "initSign \n";
    getPrivateKeyHandle(label);
    CK_MECHANISM mechanism = { CKM_ECDSA, nullptr, 0 };
    CK_RV rv = _pkcs11->C_SignInit(_session.getSession(), &mechanism, privateKey);
    if (rv != CKR_OK) {
        throw std::runtime_error("C_SignInit failed with error: " + std::to_string(rv));
    }
    return true;
}

std::vector<uint8_t> Sign::signData(const std::vector<std::uint8_t> &hash)
{
    std::cout << "signData \n";

    initSign("mykey");

    CK_BYTE signature[132];
    CK_ULONG signatureLen = sizeof(signature);

    CK_RV rv = _pkcs11->C_Sign(_session.getSession(), (CK_UTF8CHAR_PTR)hash.data(), hash.size(), signature, &signatureLen);
    if (rv != CKR_OK) {
        throw std::runtime_error("C_Sign failed with error: " + std::to_string(rv));
    }

    // Step 4: Print the signature
    std::cout << "Signature (" << signatureLen << " bytes): ";
    for (CK_ULONG i = 0; i < signatureLen; ++i) {
        printf("%02X", signature[i]);
    }
    std::cout << std::endl;
    std::vector<uint8_t> signatureByte(signature, signature + signatureLen);
    return signatureByte;
}

void Sign::getPrivateKeyHandle(const std::string &label){
        CK_ULONG objectCount;
        CK_OBJECT_CLASS objectType = CKO_PRIVATE_KEY;

        CK_ATTRIBUTE searchTemplate[] = {
            { CKA_CLASS, &objectType, sizeof(objectType) },
            { CKA_LABEL, const_cast<char*>(label.c_str()), strlen(label.c_str()) }
        };

        auto rv = _pkcs11->C_FindObjectsInit(_session.getSession(), searchTemplate, sizeof(searchTemplate)/sizeof(CK_ATTRIBUTE));
        if (rv != CKR_OK) {
            
            throw std::runtime_error("Failed C_FindObjectsInit");
        }

        rv = _pkcs11->C_FindObjects(_session.getSession(), &privateKey, 1, &objectCount);
            if (rv != CKR_OK) {
                throw std::runtime_error("Failed to find objects");
            }

        _pkcs11->C_FindObjectsFinal(_session.getSession());
        //std::cout << "Private key found: handle = " << privateKey << std::endl;
        return;
    }

// bool Sign::getAttributes(const std::string &label, CK_ATTRIBUTE* attrs){
//         getPrivateKeyHandle(label);

//         auto rv = _pkcs11->C_GetAttributeValue(_session.getSession(), privateKey, attrs, 2);
//         if (rv != CKR_OK) {
//             std::cout << rv << std::endl;;
//             throw std::runtime_error("Failed C_GetAttributeValue");
//         }
        
//         attrs[0].pValue = malloc(attrs[0].ulValueLen);
//         attrs[1].pValue = malloc(attrs[1].ulValueLen);

//         rv = _pkcs11->C_GetAttributeValue(_session.getSession(), privateKey, attrs, 2);
//         if (rv != CKR_OK) {
//             std::cout << rv << std::endl;;
//             throw std::runtime_error("Failed C_GetAttributeValue");
//         }

//         for (CK_ULONG i = 0; i < 2; i++) {
//         printf("Attribute %lu:\n", i);
//         printf("  Type: 0x%lx\n", attrs[i].type);
//         printf("  Length: %lu\n", attrs[i].ulValueLen);

//         if (attrs[i].pValue != NULL) {
//             printf("  Value: ");
//             unsigned char* val = (unsigned char*)attrs[i].pValue;
//             for (CK_ULONG j = 0; j < attrs[i].ulValueLen; j++) {
//                 printf("%02X ", val[j]);
//             }
//             printf("\n");
//         } else {
//             printf("  Value: NULL\n");
//         }
//     }
//         return true;
//     }



}  // namespace clicksharecertificateprovider