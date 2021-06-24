cmake_minimum_required(VERSION 3.6)
project(resp_gen LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../modules)

include(compilers_flags)
include(ConanInit)

conan_init()

add_executable(resp_gen main.cpp)

target_compile_definitions(${PROJECT_NAME} PUBLIC RES_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}\")
target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::nlohmann_json)
target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::fmt)
target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::toolbox)
target_link_libraries(${PROJECT_NAME} PRIVATE CONAN_PKG::boost)