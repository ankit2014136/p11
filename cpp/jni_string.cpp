#include "jni_string.h"
namespace clicksharecertificateprovider
{

JNIString::JNIString(JNIEnv &env, const jstring &input)
    : _nativeString(env.GetStringUTFChars(input, 0))
    , _input(input)
    , _env(env)
{
}

JNIString::~JNIString()
{
    _env.ReleaseStringUTFChars(_input, _nativeString);
}

const char *JNIString::operator()() const
{
    return _nativeString;
}
}  // namespace clicksharecertificateprovider