package com.barco.clickshare.productionapi;

import java.security.Key;
import java.security.KeyManagementException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.Security;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;
import java.util.ArrayList;
import java.util.Collection;

import javax.net.ssl.KeyManager;
import javax.net.ssl.SSLContext;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import com.microsoft.azure.sdk.iot.provisioning.security.SecurityProviderX509;
import com.microsoft.azure.sdk.iot.provisioning.security.exceptions.SecurityProviderException;

public class PKCS11SecurityProvider extends SecurityProviderX509{

    private String deviceId;
    private PKCS11KeyManager kmf;
    private String keyAlias;
    public PKCS11SecurityProvider(){
        try{
        Security.insertProviderAt(new PKCS11Provider(), 1);
        kmf = new PKCS11KeyManager("mykey");
        keyAlias = kmf.getClientAliases(null, null)[0];
        deviceId = extractCommonName(kmf.getCertificateChain("mykey")[0].getSubjectX500Principal().getName());
        System.out.println("deviceId= " + deviceId);
        }
        catch(CertificateException e){
            System.out.println("CertificateException: " + e.getStackTrace().toString());
        }
    }
    
    @Override
    public String getRegistrationId()
    {
        return deviceId;
    }

    @Override
    public String getClientCertificateCommonName()
    {
        return deviceId;
    }

    @Override
    public SSLContext getSSLContext() throws SecurityProviderException
    {
        try{
        TrustManager[] trustAll = new TrustManager[] {
            new X509TrustManager() {
                public java.security.cert.X509Certificate[] getAcceptedIssuers() { return null; }
                public void checkClientTrusted(java.security.cert.X509Certificate[] certs, String authType) { }
                public void checkServerTrusted(java.security.cert.X509Certificate[] certs, String authType) { }
            }
        };
        SSLContext ctx = SSLContext.getInstance("TLS");
        ctx.init(new KeyManager[]{kmf}, trustAll, new SecureRandom());
        System.out.println("SSL context initialized successfully");
        return ctx;
    }
    catch (NoSuchAlgorithmException | KeyManagementException e)
        {
            throw new SecurityProviderException(e);
        }
    }

    @Override
    public Key getClientPrivateKey() {
        try {
            Key key = kmf.getPrivateKey(keyAlias);
            if (key instanceof PKCS11PrivateKey) {
                System.out.println("Private Key found:" + keyAlias);
                return (PKCS11PrivateKey) key;
            }
        } catch (Exception e) {
            throw new IllegalStateException("Error accessing keystore", e);
        }

        throw new IllegalStateException("No client certificate found in PKCS11 keystore");
    }

    @Override
    public X509Certificate getClientCertificate() {
        try {
            Certificate cert = kmf.getCertificateChain(keyAlias)[0];
            if (cert instanceof X509Certificate) {
                System.out.println("Client certificate found:" + keyAlias);
                return (X509Certificate) cert;
            }
        } catch (Exception e) {
            throw new IllegalStateException("Error accessing keystore", e);
        }

        throw new IllegalStateException("No client certificate found in PKCS11 keystore");
    }

    @Override
    public Collection<X509Certificate> getIntermediateCertificatesChain() {
        return new ArrayList<>();
    }

    private static String extractCommonName(String subject) throws CertificateException {
        int cnIndex = subject.indexOf("CN=");
        if (cnIndex == -1) {
            throw new CertificateException("Invalid device certificate. Common name should exist in the subject");
        }

        int start = cnIndex + "CN=".length();
        String cnPart = subject.substring(start);

        int commaIndex = cnPart.indexOf(",");
        if (commaIndex != -1) {
            return cnPart.substring(0, commaIndex);
        } else {
            return cnPart;
        }
    }
}
