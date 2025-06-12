package com.barco.clickshare.productionapi;

import java.security.PrivateKey;

public class PKCS11PrivateKey implements PrivateKey {
    private final String label;
    
    public PKCS11PrivateKey(String label) {
        this.label = label;
    }

    public String getLabel() {
        System.out.println("PKCS11PrivateKey::getLabel");
        return label;
    }
    
    @Override
    public String getAlgorithm() {
        System.out.println("PKCS11PrivateKey::getAlgorithm");
        return "EC";
    }
    @Override
    public String getFormat() {
        System.out.println("PKCS11PrivateKey::getFormat");
        return null;
    }
    @Override
    public byte[] getEncoded() {
        System.out.println("PKCS11PrivateKey::getEncoded");
        return null;
    }  
}