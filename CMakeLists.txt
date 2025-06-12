cmake_minimum_required(VERSION 3.10)
project(P11)

set(LIBRARY_NAME "ClickshareCertificateProvider")

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS})
include_directories(cpp)
include_directories(include)
include_directories(exceptions)

add_library(${LIBRARY_NAME} SHARED 
        cpp/clickshare_certificate_provider_jni.cpp
        cpp/clickshare_certificate_provider.cpp
        cpp/crypto_provider_factory.cpp
        cpp/env_impl.cpp
        cpp/group_login_state.cpp
        cpp/login_guard.cpp
        cpp/login_state.cpp
        cpp/login_state_factory_impl.cpp
        cpp/login_state_manager_impl.cpp
        cpp/login_state_manager_factory_impl.cpp
        cpp/pkcs11_crypto_provider.cpp
        cpp/context.cpp
        cpp/module.cpp
        cpp/module_factory.cpp
        cpp/object_collection_factory_impl.cpp
        cpp/object_collection_impl.cpp
        cpp/slots.cpp
        cpp/slot.cpp
        cpp/p11_impl.cpp
        cpp/jni_string.cpp
        cpp/session.cpp
        cpp/engine.cpp
        cpp/openssl_impl.cpp
        cpp/pkcs11_impl.cpp
        cpp/key_pair_generator.cpp
        cpp/sign.cpp
        cpp/user_login_state.cpp
)

function(add_softhsm2)
    find_path(SOFTHSM2_INCLUDE_DIR
            NAMES pkcs11.h
            PATHS /usr/include/softhsm /usr/local/include/softhsm
    )
    find_library(SOFTHSM2_LIBRARY
            NAMES softhsm2
            PATHS /usr/lib/softhsm /usr/lib/x86_64-linux-gnu/softhsm
    )
    if (SOFTHSM2_INCLUDE_DIR AND SOFTHSM2_LIBRARY)
        message(STATUS "Found softhsm2: ${SOFTHSM2_LIBRARY}")
        include_directories(${SOFTHSM2_INCLUDE_DIR})
        target_link_libraries(${LIBRARY_NAME} PUBLIC ${SOFTHSM2_LIBRARY} ${JNI_LIBRARIES} p11)
    else()
        message(FATAL_ERROR "SoftHSM2 not found! Install it using sudo apt-get install libsofthsm2-dev")
    endif()
endfunction()

add_softhsm2()

#target_link_libraries(${LIBRARY_NAME} ${JNI_LIBRARIES} p11)
