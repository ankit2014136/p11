package com.barco.clickshare.productionapi;

import java.security.SignatureSpi;
import java.io.ByteArrayOutputStream;
import java.security.InvalidKeyException;
import java.security.PrivateKey;
import java.security.PublicKey;
import java.security.SignatureException;

public class PKCS11SignatureSpi extends SignatureSpi {
   private ByteArrayOutputStream buffer = new ByteArrayOutputStream();
   private String keyLabel;

    @Override
   protected void engineInitSign(PrivateKey privateKey) throws InvalidKeyException {
    System.out.println("PKCS11SignatureSpi::engineInitSign");
       if (!(privateKey instanceof PKCS11PrivateKey)) {
           throw new InvalidKeyException("Unsupported key type: " + privateKey.getClass());
       }
       this.keyLabel = ((PKCS11PrivateKey) privateKey).getLabel();
       buffer.reset();
       ClickshareCertificateProviderJNIImplementation.getInstance().initSign(keyLabel);
       System.out.println("PKCS11SignatureSpi::Custom PKCS11SignatureSpi initialized with PKCS11PrivateKey");
   }

   @Override
   protected void engineUpdate(byte b) throws SignatureException {
    System.out.println("PKCS11SignatureSpi::engineUpdate");
       buffer.write(b);
   }

   @Override
   protected void engineUpdate(byte[] b, int off, int len) throws SignatureException {
    System.out.println("PKCS11SignatureSpi::engineUpdate");
       buffer.write(b, off, len);
   }

   @Override
   protected byte[] engineSign() throws SignatureException {
    System.out.println("PKCS11SignatureSpi::engineSign");
       byte[] data = buffer.toByteArray();
       buffer.reset();
       System.out.println("Signing data of length: " + data.length);
       return ClickshareCertificateProviderJNIImplementation.getInstance().sign(data);  
   }
   
   @Override protected void engineSetParameter(String param, Object value) 
    {
        System.out.println("PKCS11SignatureSpi::engineSetParameter");
        return;
    }

   @Override protected Object engineGetParameter(String param) {
    System.out.println("PKCS11SignatureSpi::engineGetParameter");
        return null; 
    }

   @Override
   protected void engineInitVerify(PublicKey publicKey) throws InvalidKeyException {
    throw new UnsupportedOperationException("PKCS11SignatureSpi::Unimplemented method 'engineInitVerify'");
   }
   @Override
   protected boolean engineVerify(byte[] sigBytes) throws SignatureException {
    throw new UnsupportedOperationException("PKCS11SignatureSpi::Unimplemented method 'engineVerify'");
   }
}

