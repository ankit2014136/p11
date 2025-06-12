package com.barco.clickshare.productionapi;

import java.security.KeyManagementException;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.NoSuchProviderException;
import java.security.SecureRandom;

import javax.net.ssl.KeyManager;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import java.io.IOException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Security;
import java.security.SignatureException;
import java.security.UnrecoverableKeyException;
import java.security.cert.CertificateException;


public class ClickshareCertificateProvider {
    @SuppressWarnings("deprecation")
    public static void main(String[] args) throws NoSuchAlgorithmException, KeyManagementException, KeyStoreException, UnrecoverableKeyException, CertificateException, IOException, NoSuchProviderException, SignatureException, InvalidAlgorithmParameterException, InvalidKeyException {
 
            TrustManager[] trustAll = new TrustManager[] {
                new X509TrustManager() {
                    public java.security.cert.X509Certificate[] getAcceptedIssuers() { return null; }
                    public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) { }
                    public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) { }
                }
            };

            Security.insertProviderAt(new PKCS11Provider(), 1);
            SSLContext ctx = SSLContext.getInstance("TLS");
            ctx.init(new KeyManager[]{new PKCS11KeyManager("mykey")}, trustAll, new SecureRandom());

            // Use your SSLContext (e.g., connect to server, or create SSLEngine)
            SSLSocketFactory factory2 = ctx.getSocketFactory();
            SSLSocket socket2 = (SSLSocket) factory2.createSocket("10.98.6.21", 9876);
            socket2.startHandshake(); // triggers signature
            System.out.println("?? TLS handshake complete");


        // String config = "/tmp/pkcs.cfg";

        // Provider pkcs11Provider1 = Security.getProvider("SunPKCS11").configure(config);
        // Security.addProvider(pkcs11Provider1);

        // // Step 2: Load the KeyStore from the token
        // KeyStore ks1 = KeyStore.getInstance("PKCS11", pkcs11Provider1);
        // ks1.load(null, "ABCD1".toCharArray()); // PIN for the token
        // System.out.println("ks1: " + ks1.toString());

        // KeyManagerFactory keyManagerFactory1 = KeyManagerFactory.getInstance(KeyManagerFactory.getDefaultAlgorithm());
        // keyManagerFactory1.init(ks1, null);

        //  for (Provider p : Security.getProviders()) {
        //      System.out.println(p.toString());
        //   }


        // for (Provider provider : Security.getProviders()) {
            
        //      for (Provider.Service service : provider.getServices()) {
               
                
        //     //if ("KeyManagerFactory".equals(service.getType())) {
        //         System.out.println("Type: " + service.getType());
        //         System.out.println("Provider: " +   provider.getInfo() + "====Service " +provider.getServices());
        //     System.out.println("Algorithm: " + service.getAlgorithm() + " (Provider: " + provider.getName() + ")");
        //     //}
        //      }
        //      }

        // SSLContext sslContext1 = SSLContext.getInstance("TLSv1.2","SunPKCS11-PKCS11");
        // sslContext1.init(keyManagerFactory1.getKeyManagers(), trustAll, new SecureRandom());
        // System.out.println(sslContext1.getProvider().toString());
        
        // SSLSocketFactory factory1 = sslContext1.getSocketFactory();
        // HttpsURLConnection.setDefaultSSLSocketFactory(factory1);
        // System.out.println("SSLContext successfully initialized with HSM key.");

        // try (SSLSocket socket1 = (SSLSocket) factory1.createSocket("10.98.6.21", 9876)) {

        //     socket1.startHandshake();  // Will trigger use of your HSM-backed key
        //     System.out.println("? TLS handshake succeeded.");
        // } catch (Exception e) {
        //     System.err.println("? TLS handshake failed: " + e.getMessage());
        //     e.printStackTrace();
        //     return;
        // }

        
        // Security.addProvider(new Provider("PKCS11", 1.0, "HSM based PKCS11 Provider") {{
        //     put("Signature.SHA256withECDSA", "com.barco.clickshare.productionapi.PKCS11SignatureSpi");
        // }});

        //PKCS11PrivateKey privateKey = new PKCS11PrivateKey("mykey", null);

        // PKCS11Provider pkcs11Provider = new PKCS11Provider();
        // Security.addProvider(pkcs11Provider);

        // for (Provider p : Security.getProviders()) {
        //     System.out.println(p.toString());
        //  }


        // InputStream in = new FileInputStream("mykey_selfsigned_cert.pem");
        // CertificateFactory fac = CertificateFactory.getInstance("X.509");
        // X509Certificate cert = (X509Certificate)fac.generateCertificate(in);
        // X509Certificate[] chain = new X509Certificate[]{cert};

        // ECParameterSpec ecSpec; 
        // {
        //     KeyPairGenerator kpg = KeyPairGenerator.getInstance("EC");
        //     kpg.initialize(new ECGenParameterSpec("secp521r1"));
        //     ecSpec = ((ECPrivateKey) kpg.generateKeyPair().getPrivate()).getParams();
        // }
        //PKCS11Provider pkcs11Provider = new PKCS11Provider();
        //Security.addProvider(pkcs11Provider);
        

        
        // PKCS11PrivateKey privateKey = new PKCS11PrivateKey("mykey", null);
        // //PKCS11KeyManager keyManager = new PKCS11KeyManager("mykey", privateKey, chain);

        // //Signature signature = Signature.getInstance("SHA256withECDSA", "PKCS11");
        // //byte[] hash = MessageDigest.getInstance("SHA-512").digest("message".getBytes());
        // //signature.initSign(privateKey);


        // KeyStore ks = KeyStore.getInstance("PKCS11KS", "PKCS11");
        // ks.load(null, null);
        // System.out.println("Key: " + ks.getKey("mykey", null));
        // System.out.println("cert chain: " + ks.getCertificateChain("mykey"));

        // //PKCS11KeyManagerFactory keyManagerFactory = PKCS11KeyManagerFactory.getInstance(pkcs11Provider, "PKCS11X509");
        // //keyManagerFactory.init(ks, null);

        // KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance("PKCS11X509", "PKCS11");
        // keyManagerFactory.init(ks, null);

         //for(KeyManager km : keyManagerFactory.getKeyManagers()){
         //    System.out.println("Key manager: " + km.toString());
        // }
        
        //KeyManager[] kms = new KeyManager[] {
        //    keyManager  // HSM label
        //};

        // for (Provider provider : Security.getProviders()) {
            
        //      for (Provider.Service service : provider.getServices()) {
               
                
        //     if ("KeyManagerFactory".equals(service.getType())) {
        //         System.out.println("Type: " + service.getType());
        //         System.out.println("Provider: " +   provider.getInfo() + "====Service " +provider.getServices());
        //     System.out.println("Algorithm: " + service.getAlgorithm() + " (Provider: " + provider.getName() + ")");
        //     }
        //      }
        //      }

        // Signature signature = Signature.getInstance("SHA256withECDSA", "PKCS11");
        // byte[] hash = MessageDigest.getInstance("SHA-512").digest("message".getBytes());
        // signature.initSign(privateKey);
        // signature.update(hash);
        // signature.sign();

        
        
        // SSLContext sslContext = SSLContext.getInstance("TLSv1.2", "PKCS11");
        // sslContext.init(keyManagerFactory.getKeyManagers(), trustAll, new SecureRandom());
        // System.out.println(sslContext.getProvider().toString());
        
        // SSLSocketFactory factory = sslContext.getSocketFactory();
        // HttpsURLConnection.setDefaultSSLSocketFactory(factory);
        // System.out.println("SSLContext successfully initialized with HSM key.");

        // try (SSLSocket socket = (SSLSocket) factory.createSocket("10.98.6.21", 9876)) {

        //     socket.startHandshake();  // Will trigger use of your HSM-backed key
        //     System.out.println("? TLS handshake succeeded.");
        // } catch (Exception e) {
        //     System.err.println("? TLS handshake failed: " + e.getMessage());
        //     e.printStackTrace();
        // }
        
        //ClickshareCertificateProviderJNIImplementation  s = new ClickshareCertificateProviderJNIImplementation ();

        
        //Boolean result = s.generatePrivateKeyPair("", 1, "/usr/lib/softhsm/");
        //if (Boolean.TRUE.equals(result)){
        //    System.out.println("Keys generated successfully");
        //}

        //PKCS11PrivateKey privateKey = new PKCS11PrivateKey("");
        //byte[] hash = MessageDigest.getInstance("SHA-512").digest("message".getBytes());
        //byte[] signature = privateKey.sign(hash);
        //StringBuilder sb = new StringBuilder();
        //for (byte b : signature) {
        //    sb.append(String.format("%02X", b));
        //}
        //System.out.println(sb.toString());

        /* KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
        keyStore.load(null);

        X509Certificate leafCertificate = null;
        Collection<X509Certificate> signerCertificates = null;

        // Load Alias cert and private key to key store
        int noOfCerts = signerCertificates.size() + 1;
        X509Certificate[] certs = new X509Certificate[noOfCerts];
        int i = 0;
        certs[i++] = leafCertificate;

        // Load the chain of signer cert to keystore
        for (X509Certificate c : signerCertificates)
        {
            certs[i++] = c;
        }

        keyStore.setKeyEntry("mykey", privateKey, null, certs);

        // create key manager factory and obtain x509 key manager
        KeyManagerFactory keyManagerFactory = KeyManagerFactory.getInstance(KeyManagerFactory.getDefaultAlgorithm());
        keyManagerFactory.init(keyStore, null);

        //PKCS11KeyManager keyManager = new PKCS11KeyManager("mykey", privateKey, null);
        TrustManagerFactory tmf = TrustManagerFactory.getInstance(null);
        try {
            tmf.init((KeyStore)null);
        } catch (KeyStoreException e) {
            e.printStackTrace();
            return;
        }

        SSLContext sslContext = SSLContext.getInstance("TLS");

        sslContext.init(keyManagerFactory.getKeyManagers(), null, new SecureRandom()); */

        //ctx.init(new KeyManager[]{keyManager}, tmf.getTrustManagers(), SecureRandom());
        return;
        
    }
}
