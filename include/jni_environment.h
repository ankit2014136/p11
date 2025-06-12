#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_JNI_ENVIRONMENT_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_JNI_ENVIRONMENT_H

#include <jni.h>

#include <string>
#include <vector>

#include "jni_string.h"

namespace clicksharecertificateprovider
{
class JNIEnvironment
{
public:
    JNIEnvironment(JNIEnv *env);
    ~JNIEnvironment() = default;

    JNIString convertToJNIString(const jstring &input) const;
    void appendStringToObject(const jobject &object, const std::string &input) const;
    jboolean convertToJNIBoolean(bool input) const;
    std::vector<std::uint8_t> convertToNativeByteArray(const jbyteArray &data) const;

private:
    JNIEnv &_env;
};
} // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_JNI_ENVIRONMENT_H