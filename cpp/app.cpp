
#include <iostream>
#include "p11_impl.h"
#include "clickshare_certificate_provider.h"

int main() {
    std::filesystem::path libPath = "/usr/lib/softhsm/";
    //auto p11Impl = std::make_shared<clicksharecertificateprovider::P11Impl>();
    //clicksharecertificateprovider::PKCS11CryptoProvider* crypto_provider = 
    //new clicksharecertificateprovider::PKCS11CryptoProvider(libPath,p11Impl);


    clicksharecertificateprovider::ClickshareCertificateProvider prov = clicksharecertificateprovider::ClickshareCertificateProvider(libPath);

return 0;
}
