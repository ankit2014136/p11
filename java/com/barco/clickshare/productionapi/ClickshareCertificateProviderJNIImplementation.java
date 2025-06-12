package com.barco.clickshare.productionapi;


public class ClickshareCertificateProviderJNIImplementation  {

    static {
        System.loadLibrary("ClickshareCertificateProvider");
    }

    private static final ClickshareCertificateProviderJNIImplementation INSTANCE = new ClickshareCertificateProviderJNIImplementation();

    private ClickshareCertificateProviderJNIImplementation() {}

    public static ClickshareCertificateProviderJNIImplementation getInstance() {
        return INSTANCE;
    }

    public native boolean initSign(String keyLabel);
    public native byte[] sign(byte[] hash);
    public native byte[] readCertificate(String keyLabel);
}