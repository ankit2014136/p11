#include "key_pair_generator.h"

#include <vector>
#include <stdexcept>
#include<iostream>

namespace clicksharecertificateprovider
{
KeyPairGenerator::KeyPairGenerator(long unsigned int slotId, std::string pin, std::shared_ptr<LoginStateManager> loginStateManager, std::shared_ptr<Pkcs11> pkcs11)
    : _pkcs11(pkcs11)
    , _session(slotId, std::move(pin), loginStateManager, pkcs11)
{
}

void KeyPairGenerator::generateKeyPairWithECPrime256Curve()
{
    const std::string kCommonName{"mykey"};
    CK_MECHANISM mechanism{ CKM_EC_KEY_PAIR_GEN, nullptr, 0 };
    CK_OBJECT_HANDLE publicKey;
    CK_OBJECT_HANDLE privateKey;
    CK_BYTE prime256v1OID[]{0x06, 0x08, 0x2A, 0x86, 0x48, 0xCE, 0x3D, 0x03, 0x01, 0x07};
    CK_KEY_TYPE keyType = CKK_EC;
    CK_BBOOL trueValue = CK_TRUE;

    //auto publicKeyTemplate = createPublicKeyTemplate();
    //auto privateKeyTemplate = createPrivateKeyTemplate();
    CK_ATTRIBUTE publicKeyTemplate[] = {
        {CKA_KEY_TYPE, &keyType, sizeof(keyType)},
        {CKA_EC_PARAMS, prime256v1OID, sizeof(prime256v1OID)},
        {CKA_LABEL, (CK_VOID_PTR)kCommonName.c_str(), kCommonName.size()},
        {CKA_TOKEN,  &trueValue, sizeof(trueValue)},
        {CKA_VERIFY, &trueValue, sizeof(trueValue)}
    };
    CK_ATTRIBUTE privateKeyTemplate[] = {
        {CKA_KEY_TYPE, &keyType, sizeof(keyType)},
        {CKA_SIGN, &trueValue, sizeof(trueValue)},
        {CKA_LABEL, (CK_VOID_PTR)kCommonName.c_str(), kCommonName.size()},
        {CKA_TOKEN,  &trueValue, sizeof(trueValue)},
        {CKA_PRIVATE, &trueValue, sizeof(trueValue)}
    };
    const auto rv = _pkcs11->C_GenerateKeyPair(_session.getSession(), &mechanism,
                        publicKeyTemplate, sizeof(publicKeyTemplate)/sizeof(CK_ATTRIBUTE),
                        privateKeyTemplate, sizeof(privateKeyTemplate)/sizeof(CK_ATTRIBUTE),
                        &publicKey, &privateKey);
    if (rv != CKR_OK) {
        std::cout << "Key pair generation failed. Error code: 0x" << std::hex << rv << std::endl;
        throw std::runtime_error("Failed to generate key pair");
    }
}
}  // namespace clicksharecertificateprovider