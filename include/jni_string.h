#ifndef CLICKSHARE_CERTIFICATE_PROVIDER_JNISTRING_H
#define CLICKSHARE_CERTIFICATE_PROVIDER_JNISTRING_H

#include <jni.h>

namespace clicksharecertificateprovider
{

class JNIString
{
public:
    JNIString(JNIEnv &env, const jstring &input);
    ~JNIString();
    const char *operator()() const;

private:
    JNIEnv &_env;
    const jstring &_input;
    const char *_nativeString;
};

}  // namespace clicksharecertificateprovider
#endif  // CLICKSHARE_CERTIFICATE_PROVIDER_JNISTRING_H