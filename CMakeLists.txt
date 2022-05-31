cmake_minimum_required(VERSION 3.22)
project(category_script)

set(CMAKE_CXX_STANDARD 11)

set(ROOT_DIR "/Users/mason/Desktop/IME_Scripts/category_script/")

include_directories("${ROOT_DIR}includes")

include(FetchContent) # Support JSON

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.10.5/json.tar.xz)
FetchContent_MakeAvailable(json)

# 设置HTTPS环境变量
set(BREW_OPENSSL_PREFIX "/usr/local/opt/openssl@1.1")
set(OPENSSL_ROOT_DIR "${BREW_OPENSSL_PREFIX}/")
set(OPENSSL_INCLUDE_DIR "${BREW_OPENSSL_PREFIX}/include")
set(OPENSSL_CRYPTO_LIBRARY "${BREW_OPENSSL_PREFIX}/lib/libcrypto.1.1.dylib")
set(OPENSSL_USE_STATIC_LIBS TRUE)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
if(OPENSSL_FOUND)
    set(HTTPLIB_IS_USING_OPENSSL TRUE)
    message("OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
    message("OpenSSL libraries: ${OPENSSL_LIBRARIES}")
endif()

add_executable(category_script main.cpp ba_request/ba_request.cpp ba_request/qq_music_model.cpp ba_request/music_request_api.cpp ba_request/movie_request_api.cpp ba_request/amap_city_model.cpp ba_request/company_request_api.cpp ba_request/Chameleon.cpp ba_request/ConfigFile.cpp ba_request/config_reader.cpp ba_request/music_lysic_request_api.cpp ba_request/app_request_api.cpp)

target_link_libraries(category_script PRIVATE nlohmann_json::nlohmann_json)  # project name must defined before the add_executable

target_link_libraries(${PROJECT_NAME} PUBLIC
        $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::SSL>
        $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:OpenSSL::Crypto>)

target_compile_definitions(${PROJECT_NAME} PUBLIC
        $<$<BOOL:${HTTPLIB_IS_USING_OPENSSL}>:CPPHTTPLIB_OPENSSL_SUPPORT>
        )
