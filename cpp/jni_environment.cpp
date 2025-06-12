#include "jni_environment.h"

namespace clicksharecertificateprovider
{

JNIEnvironment::JNIEnvironment(JNIEnv *env)
    : _env(*env)
{
}

JNIString JNIEnvironment::convertToJNIString(const jstring &input) const
{
    return JNIString(_env, input);
}

void JNIEnvironment::appendStringToObject(const jobject &object, const std::string &input) const
{
    jstring jniString = _env.NewStringUTF(input.c_str());
    jclass stringBuilderClass = _env.GetObjectClass(object);
    jmethodID appendMethod = _env.GetMethodID(stringBuilderClass, "append", "(Ljava/lang/String;)Ljava/lang/StringBuilder;");
    _env.CallObjectMethod(object, appendMethod, jniString);
}

jboolean JNIEnvironment::convertToJNIBoolean(bool input) const
{
    return input ? JNI_TRUE : JNI_FALSE;
}

std::vector<std::uint8_t> JNIEnvironment::convertToNativeByteArray(const jbyteArray &data) const
{
    const jsize dataLength = _env.GetArrayLength(data);
    if (dataLength < 0) {
        return {};
    }

    std::vector<std::uint8_t> nativeData(dataLength);
    _env.GetByteArrayRegion(data, 0, dataLength, reinterpret_cast<jbyte *>(nativeData.data()));
    return nativeData;
}

}  // namespace clicksharecertificateprovider