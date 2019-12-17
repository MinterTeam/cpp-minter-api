cmake_minimum_required(VERSION 3.10)
project(minter_api
        VERSION 0.1.0
        DESCRIPTION "Minter C++ REST API SDK: access web services like explorer, gate and liquidity provider (bip.dev)"
        HOMEPAGE_URL "https://github.com/MinterTeam/cpp-minter-api"
        LANGUAGES CXX
        )

if (WIN32)
	execute_process(
		COMMAND cmd /C "echo ${CMAKE_PROJECT_VERSION} > ${CMAKE_CURRENT_SOURCE_DIR}/version"
	)
else ()
	execute_process(
		COMMAND bash -c "echo ${CMAKE_PROJECT_VERSION} > ${CMAKE_CURRENT_SOURCE_DIR}/version"
	)
endif ()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(ENABLE_SHARED OFF CACHE BOOL "Build shared lib instead of static")

include(modules/compilers_flags.cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)

include(ConanInit)
add_conan_remote(bincrafters https://api.bintray.com/conan/bincrafters/public-conan)
add_conan_remote(scatter https://api.bintray.com/conan/edwardstock/scatter)
add_conan_remote(minter https://api.bintray.com/conan/minterteam/minter)
add_conan_remote(edwardstock https://api.bintray.com/conan/edwardstock/conan-public)

conan_init()


if (APPLE)
	set(CMAKE_MACOSX_RPATH OFF)
endif (APPLE)

add_definitions(-DMINTER_EXPLORER_API="https://texasnet.explorer-api.minter.network/api/v1/")
add_definitions(-DMINTER_GATE_API="https://texasnet.gate-api.minter.network/api/v1/")
add_definitions(-DMINTER_LP_API="https://api.bip.dev/api/v1/")


configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cfg/minter_api_config.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/minter/api/minter_api_config.h
)


set(HEADERS
    include/minter/api/explorer/base.h
    include/minter/api/explorer/repository.h
    include/minter/api/explorer/results.hpp
    include/minter/api/gate/base.h
    include/minter/api/gate/repository.h
    include/minter/api/gate/results.hpp
    include/minter/api/gate/exchange_calculator.h
    include/minter/api/liquidity/base.h
    include/minter/api/liquidity/repository.h
    include/minter/api/liquidity/results.hpp
    )

set(SOURCES
    ${HEADERS}
    src/base_repository.cpp
    src/explorer_results.cpp
    src/explorer_repository.cpp
    src/gate_repository.cpp
    src/liquidity_repository.cpp

    )

add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} CONAN_PKG::boost)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::minter_tx)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::toolbox)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::httb)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::nlohmann_json)

# JSON-Struct response generator
set(PROJECT_NAME_RG resp_gen)
add_executable(${PROJECT_NAME_RG} src/resp_generator/main.cpp)
target_compile_definitions(${PROJECT_NAME_RG} PUBLIC RES_PATH=\"${CMAKE_CURRENT_SOURCE_DIR}\")
target_link_libraries(${PROJECT_NAME_RG} CONAN_PKG::nlohmann_json)
target_link_libraries(${PROJECT_NAME_RG} CONAN_PKG::fmt)
target_link_libraries(${PROJECT_NAME_RG} CONAN_PKG::toolbox)
target_link_libraries(${PROJECT_NAME_RG} CONAN_PKG::boost)

if (ENABLE_MINTER_API_TESTS)
	include(modules/tests.cmake)
endif ()