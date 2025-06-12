#include "engine.h"

#include <stdexcept>

namespace
{
const std::string kSoPath{"libpkcs11.so"};
const std::string kModulePath{"libsofthsm2.so"};
const std::string kId{"pkcs11"};
constexpr int kOptionalCommand{};
}  // namespace

namespace clicksharecertificateprovider
{
Engine::Engine(std::shared_ptr<OpenSSL> openssl, const std::filesystem::path &libraryPath)
    : _openssl(std::move(openssl))
    , _engine(initializeEngine(libraryPath))
{
}


Engine::ENGINE_PTR Engine::initializeEngine(const std::filesystem::path &libraryPath)
{
    _openssl->ENGINE_load_builtin_engines();

    ENGINE *engine= _openssl->ENGINE_by_id("dynamic");

    _openssl->ENGINE_ctrl_cmd_string(engine, "SO_PATH", (libraryPath  / kSoPath).string().c_str(), 0);
    _openssl->ENGINE_ctrl_cmd_string(engine, "ID", kId.c_str(), 0);

    if (_openssl->ENGINE_set_default(engine, ENGINE_METHOD_ALL) != 1) {
        throw std::runtime_error("failed to set default");
    }

    if (!_openssl->ENGINE_ctrl_cmd_string(engine, "LIST_ADD", "1", 0)){
        throw std::runtime_error("engine failed to add list");
    }

    if (!_openssl->ENGINE_ctrl_cmd_string(engine, "LOAD", NULL, 0)){
        throw std::runtime_error("engine failed to load");
    }

    if (!_openssl->ENGINE_ctrl_cmd_string(engine, "MODULE_PATH", (libraryPath  / kModulePath).string().c_str(), kOptionalCommand)) {
        throw std::runtime_error("failed to set module path");
    }

    if (!_openssl->ENGINE_init(engine)) {
        throw std::runtime_error("engine failed to initialize");
    }

    return ENGINE_PTR(engine, [this](ENGINE* e) {
        _openssl->ENGINE_free(e);
    });
}
} // namespace clicksharecertificateprovider