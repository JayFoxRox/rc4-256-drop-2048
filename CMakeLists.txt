cmake_minimum_required(VERSION 3.7)

set(C_STANDARD 99)

find_package(OpenSSL REQUIRED)

include_directories(${OPENSSL_INCLUDE_DIR})

add_executable(rc4-256-drop-2048 main.c)
target_link_libraries(rc4-256-drop-2048 ${OPENSSL_LIBRARIES})
