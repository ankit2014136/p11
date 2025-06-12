#include "session.h"
#include <iostream>

#include "invalid_input_exception.h"
#include "session_exception.h"

namespace
{
void checkRv(CK_RV rv, const std::string &message)
{
    if (rv != CKR_OK) {
        throw clicksharecertificateprovider::SessionException(message);
    }
}
}   // namespace

namespace clicksharecertificateprovider
{
Session::Session(long unsigned int slotId, const std::string pin, std::shared_ptr<LoginStateManager> loginStateManager, std::shared_ptr<Pkcs11> pkcs11)
    : _loginStateManager(loginStateManager)
    , _pkcs11(std::move(pkcs11))
{
    open(slotId);
    login(pin);
}

Session::~Session()
{
    logout();
    close();
}

void Session::open(long unsigned int slotId)
{
    _loginStateManager->changeLoginState(UserType::User);
    const auto rv = _pkcs11->C_OpenSession(slotId, CKF_SERIAL_SESSION | CKF_RW_SESSION, nullptr, nullptr, &_session);
    checkRv(rv, "Failed to open session");
    std::cout << "Session::opened.\n";
}

void Session::close()
{
    std::ignore = _pkcs11->C_CloseSession(_session);
    std::cout << "Session::closed.\n";
}

void Session::login(const std::string &pin)
{
    const auto rv = _pkcs11->C_Login(_session, CKU_USER, (CK_UTF8CHAR_PTR)pin.c_str(), pin.size());
    checkRv(rv, "Failed to login");
    std::cout << "Session::login\n";
}

void Session::logout()
{
    std::ignore = _pkcs11->C_Logout(_session);
    std::cout << "Session::logout.\n";
}
}  // namespace clicksharecertificateprovider