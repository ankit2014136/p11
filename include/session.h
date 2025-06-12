#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_SESSION_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_SESSION_H

#include <memory>
#include <string>

#include "login_state_manager.h"
#include "pkcs11_wrapper.h"

namespace clicksharecertificateprovider
{
class Session
{
public:
    Session(long unsigned int slotId, const std::string pin, std::shared_ptr<LoginStateManager> loginStateManager, std::shared_ptr<Pkcs11> pkcs11);
    ~Session();

    CK_SESSION_HANDLE getSession() const { return _session; }

private:
    void open(long unsigned int slotId);
    void close();
    void login(const std::string &pin);
    void logout();

    std::shared_ptr<LoginStateManager> _loginStateManager;
    std::shared_ptr<Pkcs11> _pkcs11;
    CK_SESSION_HANDLE _session{};
};
}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_SESSION_H