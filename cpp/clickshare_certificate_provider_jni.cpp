#include <string>

#include <jni.h>

#include "clickshare_certificate_provider.h"

#include "jni_string.h"

#ifdef __cplusplus
extern "C" {
#endif

using namespace clicksharecertificateprovider;

JNIEXPORT jboolean JNICALL
Java_com_barco_clickshare_productionapi_ClickshareCertificateProviderJNIImplementation_generatePrivateKeyPair(
    JNIEnv *env,
    jobject obj,
    jstring algorithm,
    jint keySize)
{
    const JNIString nativeAlgorithm{*env, algorithm};

    ClickshareCertificateProvider provider{};

    const bool result = provider.generatePrivateKeyPair(nativeAlgorithm(), keySize);
    return result ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_barco_clickshare_productionapi_ClickshareCertificateProviderJNIImplementation_initSign(
    JNIEnv *env,
    jobject obj,
    jstring label)
{
    const JNIString nativeLabel{*env, label};

    ClickshareCertificateProvider provider{};
    const bool result = provider.initSign(nativeLabel());
    return result ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jbyteArray JNICALL
Java_com_barco_clickshare_productionapi_ClickshareCertificateProviderJNIImplementation_sign(
    JNIEnv *env,
    jobject obj,
    jbyteArray hash)
{
    ClickshareCertificateProvider provider{};
    jsize len = env->GetArrayLength(hash);
    std::vector<std::uint8_t> msgBytes(len);
    env->GetByteArrayRegion(hash, 0, len, reinterpret_cast<jbyte*>(msgBytes.data()));
    std::vector<uint8_t> signature = provider.sign(msgBytes);
    jbyteArray result = env->NewByteArray(signature.size());
    env->SetByteArrayRegion(result, 0, signature.size(), reinterpret_cast<const jbyte*>(signature.data()));
    return result;
}

/* JNIEXPORT jobjectArray JNICALL Java_com_barco_clickshare_productionapi_ClickshareCertificateProviderJNIImplementation_getKeyAttributes(
    JNIEnv *env,
    jobject obj,
    jstring label){
        const JNIString nativeLabel{*env, label};

        CK_ATTRIBUTE attrs[] = {
            { CKA_VALUE, NULL, 0 },
            { CKA_EC_PARAMS, NULL, 0 }
        };

        ClickshareCertificateProvider provider{};
        provider.getAttributes(nativeLabel(), attrs);

        // Prepare Java CKAttribute class
    jclass attrClass = env->FindClass("com/barco/clickshare/productionapi/CK_ATTRIBUTE");
    if (attrClass == nullptr) {
        return nullptr;
    }
    jmethodID constructor = env->GetMethodID(attrClass, "<init>", "(JLjava/lang/Object;)V");

    // First attribute (CKA_ID)
    jbyteArray valueArray = env->NewByteArray(attrs[0].ulValueLen);
    env->SetByteArrayRegion(valueArray, 0, attrs[0].ulValueLen, reinterpret_cast<jbyte*>(attrs[0].pValue));
    jobject attrObj = env->NewObject(attrClass, constructor, static_cast<jlong>(attrs[0].type), valueArray);

    // Second attribute (CKA_EC_PARAMS)
    jbyteArray valueArray1 = env->NewByteArray(attrs[1].ulValueLen);
    env->SetByteArrayRegion(valueArray1, 0, attrs[1].ulValueLen, reinterpret_cast<jbyte*>(attrs[1].pValue));
    jobject attrObj1 = env->NewObject(attrClass, constructor, static_cast<jlong>(attrs[1].type), valueArray1);

    // Create and return array
    jobjectArray result = env->NewObjectArray(2, attrClass, nullptr);
    if (result == nullptr) {
        return nullptr;
    }
    env->SetObjectArrayElement(result, 0, attrObj);
    env->SetObjectArrayElement(result, 1, attrObj1);

    free(attrs[0].pValue);
    free(attrs[1].pValue);

    return result;
    } */

JNIEXPORT jbyteArray JNICALL
Java_com_barco_clickshare_productionapi_ClickshareCertificateProviderJNIImplementation_readCertificate(
    JNIEnv *env,
    jobject obj,
    jstring label)
{
    const JNIString nativeLabel{*env, label};

    ClickshareCertificateProvider provider{};

    std::vector<unsigned char> result;
    try {
        result = provider.readCertificate(nativeLabel());
    } catch (const std::exception &e) {
        env->ThrowNew(env->FindClass("java/lang/Exception"), e.what());
        return env->NewByteArray(0);
    }

    jbyteArray convertedResult = env->NewByteArray(result.size());
    env->SetByteArrayRegion(convertedResult, 0, result.size(), (const jbyte *)result.data());

    return convertedResult;
}

#ifdef __cplusplus
}
#endif