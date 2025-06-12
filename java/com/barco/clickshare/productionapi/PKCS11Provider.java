package com.barco.clickshare.productionapi;

import java.security.Provider;

public class PKCS11Provider extends Provider {
    public PKCS11Provider(){
        super("PKCS11", "1.0", "HSM based PKCS11 Provider");
        put("Signature.SHA256withECDSA", "com.barco.clickshare.productionapi.PKCS11SignatureSpi");  
    }
}

