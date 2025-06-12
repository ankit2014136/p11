#include "pkcs11_crypto_provider.h"

#include <stdexcept>
#include <vector>
#include <iostream>

#include "key_pair_generator.h"
#include "slot.h"
#include "module_factory.h"
#include "login_guard.h"

namespace
{
const std::string kLabel{"mytoken"};
const std::string kSoPin{"ABCD"};
const std::string kUserPin{"ABCD"};
}

namespace clicksharecertificateprovider
{
PKCS11CryptoProvider::PKCS11CryptoProvider(
    std::unique_ptr<LoginStateFactory> loginStateFactory,
    std::unique_ptr<LoginStateManagerFactory> loginStateManagerFactory,
    const std::filesystem::path &libraryDir,
    std::shared_ptr<P11> p11,
    std::shared_ptr<Pkcs11> pkcs11,
    std::shared_ptr<OpenSSL> openssl,
    std::shared_ptr<Engine> engine,
    std::unique_ptr<ObjectCollectionFactory> objectCollectionFactory)
    : _libraryDir(libraryDir)
    , _p11(std::move(p11))
    , _pkcs11(std::move(pkcs11))
    , _openssl(std::move(openssl))
    , _engine(std::move(engine))
    , _context(std::make_shared<Context>(_p11))
    , _loginStateManager(loginStateManagerFactory->createLoginStateManager(
        std::move(loginStateFactory), 
        std::make_unique<ModuleFactory>(libraryDir, _p11, _pkcs11, _context),
        UserType::SecurityOfficer))
    //, _module(std::make_unique<Module>(_p11, _pkcs11, _context, libraryDir / "libsofthsm2.so"))
    , _objectCollectionFactory(std::move(objectCollectionFactory))
    , _slots(_p11, _context)
{
    initToken();
    initPin(kUserPin);
}

void PKCS11CryptoProvider::initToken()
{
    _loginStateManager->changeLoginState(UserType::SecurityOfficer);
    auto slot = _slots.getAvailableSlot(kLabel);
    auto token = slot->token;
    if (token->initialized) {
        std::cout << "token already initialized\n";
        return;
    }
    if (_p11->PKCS11_init_token(token, kSoPin.c_str(), kLabel.c_str()) != 0) {
        throw std::runtime_error("Failed to initialize token");
    }
    std::cout << "init token success \n";
}

bool PKCS11CryptoProvider::initPin(const std::string &pin)
{
    Slot slot{_p11, _slots.getAvailableSlot(kLabel)};
    if (slot.isUserPinSet()) {
        std::cout << "User pin alreday set. \n";
        return true;
    }

    LoginGuard loginGuard{_loginStateManager, slot, kSoPin, UserType::SecurityOfficer};
    const int ret = _p11->PKCS11_init_pin(slot.getInternal()->token, pin.c_str());
    if (ret != 0) {
        throw std::runtime_error("User PIN initialization failed");
    }
    std::cout << "User Pin set.\n";
    return true;
}

bool PKCS11CryptoProvider::generateKeyPair(const std::string & /*algorithm*/, int /*keySize*/)
{
    const auto slotId = _p11->PKCS11_get_slotid_from_slot(_slots.getAvailableSlot(kLabel));
    std::cout << "slotId = " << slotId << "\n";
    KeyPairGenerator keyPairGenerator{slotId, kUserPin,  _loginStateManager, _pkcs11};
    std::cout << "generate keys \n";
    keyPairGenerator.generateKeyPairWithECPrime256Curve();
    return true;
}

bool PKCS11CryptoProvider::initSign(const std::string &label)
{
    const auto slotId = _p11->PKCS11_get_slotid_from_slot(_slots.getAvailableSlot(kLabel));
    Sign sign{slotId, kUserPin,  _loginStateManager, _pkcs11};
    return sign.initSign(label);
}

std::vector<uint8_t> PKCS11CryptoProvider::sign(const std::vector<std::uint8_t> &hash)
{
    const auto slotId = _p11->PKCS11_get_slotid_from_slot(_slots.getAvailableSlot(kLabel));
    Sign sign{slotId, kUserPin,  _loginStateManager, _pkcs11};
    return sign.signData(hash);
}

// bool PKCS11CryptoProvider::getAttributes(const std::string &label, CK_ATTRIBUTE* attrs)
// {
//     const auto slotId = _p11->PKCS11_get_slotid_from_slot(_slots.getAvailableSlot(kLabel));
//     Sign sign{slotId, kUserPin,  _loginStateManager, _pkcs11};
//     return sign.getAttributes(label, attrs);
// }

std::vector<unsigned char> PKCS11CryptoProvider::readCertificate(const std::string &label)
{
    auto objectCollection = _objectCollectionFactory->createObjectCollection(_loginStateManager, _slots.getAvailableSlot(kLabel), kUserPin);
    return objectCollection->readObjectByLabel(CKO_CERTIFICATE, label);
}

}  // namespace clicksharecertificateprovider