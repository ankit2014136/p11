package com.barco.clickshare.productionapi;

import javax.net.ssl.X509ExtendedKeyManager;

import java.io.ByteArrayInputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.net.Socket;
import java.security.Principal;
import java.security.PrivateKey;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;

public class PKCS11KeyManager extends X509ExtendedKeyManager {
    private String alias;

    PKCS11KeyManager(String alias){
        this.alias = alias;
    }

   @Override
   public String chooseClientAlias(String[] keyType, Principal[] issuers, Socket socket) {
    System.out.println("PKCS11KeyManager::chooseClientAlias");
       return alias;
   }
   @Override
   public String chooseServerAlias(String keyType, Principal[] issuers, Socket socket) {
    System.out.println("PKCS11KeyManager::chooseServerAlias");
       return alias;
   }
   @Override
   public X509Certificate[] getCertificateChain(String alias) {
    System.out.println("PKCS11KeyManager::getCertificateChain");
       try {
            byte[] certBytes = ClickshareCertificateProviderJNIImplementation.getInstance().readCertificate(alias);
            //InputStream in = new FileInputStream("mykey_selfsigned_cert.pem");
            CertificateFactory fac = CertificateFactory.getInstance("X.509");
            X509Certificate cert = (X509Certificate)fac.generateCertificate(new ByteArrayInputStream(certBytes));
            System.out.println(cert.getPublicKey());
            X509Certificate[] chain = new X509Certificate[]{cert};
            return chain;
        }
        catch (CertificateException e) {
            e.printStackTrace();
        }
         return null;
   }
   @Override
   public PrivateKey getPrivateKey(String alias) {
    System.out.println("PKCS11KeyManager::getPrivateKey");
    return new PKCS11PrivateKey(alias);
        
   }
   @Override
   public String[] getClientAliases(String keyType, Principal[] issuers) {
    System.out.println("PKCS11KeyManager::getClientAliases");
       return new String[]{alias};
   }
   @Override
   public String[] getServerAliases(String keyType, Principal[] issuers) {
    System.out.println("PKCS11KeyManager::getServerAliases");
       return new String[]{alias};
   }
}
