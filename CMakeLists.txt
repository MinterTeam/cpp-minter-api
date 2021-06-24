cmake_minimum_required(VERSION 3.6)
project(minter_api
        VERSION 0.2.0
        DESCRIPTION "Minter C++ REST API SDK: access web services like explorer, gate and liquidity provider (bip.dev)"
        HOMEPAGE_URL "https://github.com/MinterTeam/cpp-minter-api"
        LANGUAGES CXX
        )

include(CheckIncludeFileCXX)
check_include_file_cxx("optional" HAVE_CXX_OPTIONAL)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cfg/version.in ${CMAKE_CURRENT_SOURCE_DIR}/version @ONLY NEWLINE_STYLE UNIX)

set(CMAKE_CXX_STANDARD 17)
set(ENABLE_SHARED OFF CACHE BOOL "Build shared lib instead of static")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
include(compilers_flags)

include(ConanInit)
add_conan_remote(minter https://minter.jfrog.io/artifactory/api/conan/conan)
add_conan_remote(edwardstock https://edwardstock.jfrog.io/artifactory/api/conan/conan)

conan_init()


option(MINTER_TESTNET "Build app for testnet environment" Off)

if (MINTER_TESTNET)
	set(MINTER_TESTNET_NAME "testnet")
	set(MINTER_CHAIN_ID "minter::chain_id::testnet")

	set(MINTER_DEFAULT_COIN "MNT")
	set(MINTER_EXPLORER_API_V "v2")
	set(MINTER_GATE_API_V "v2")
	set(MINTER_EXPLORER_API "https://explorer-api.${MINTER_TESTNET_NAME}.minter.network/api/${MINTER_EXPLORER_API_V}/")
	set(MINTER_EXPLORER_FRONT "https://explorer.${MINTER_TESTNET_NAME}.minter.network")
	set(MINTER_GATE_API "https://gate-api.${MINTER_TESTNET_NAME}.minter.network/api/${MINTER_GATE_API_V}/")
	set(MINTER_WS_URL "wss://explorer-rtm.${MINTER_TESTNET_NAME}.minter.network/connection/websocket")
	set(MINTER_COIN_AVATAR_URL "https://my.apps.minter.network/api/v1/avatar/by/coin/")
	set(MINTER_ADDRESS_AVATAR_URL "https://my.apps.minter.network/api/v1/avatar/by/address/")
	set(MINTER_EXPLORER_STATIC_URL "https://explorer-static.${MINTER_TESTNET_NAME}.minter.network")
else ()
	set(MINTER_CHAIN_ID "minter::chain_id::mainnet")

	set(MINTER_EXPLORER_API_V "v2")
	set(MINTER_GATE_API_V "v2")
	set(MINTER_DEFAULT_COIN "BIP")
	set(MINTER_EXPLORER_API "https://explorer-api.minter.network/api/${MINTER_EXPLORER_API_V}/")
	set(MINTER_EXPLORER_FRONT "https://explorer.minter.network")
	set(MINTER_GATE_API "https://gate-api.apps.minter.network/api/${MINTER_GATE_API_V}/")
	set(MINTER_WS_URL "wss://explorer-rtm.apps.minter.network/connection/websocket")
	set(MINTER_COIN_AVATAR_URL "https://my.apps.minter.network/api/v1/avatar/by/coin/")
	set(MINTER_ADDRESS_AVATAR_URL "https://my.apps.minter.network/api/v1/avatar/by/address/")
	set(MINTER_EXPLORER_STATIC_URL "https://explorer-static.minter.network")
endif ()



configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cfg/minter_api_config.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/include/minter/api/minter_api_config.h
)


set(HEADERS
    include/minter/api/explorer/base.h
    include/minter/api/explorer/explorer_repo.h
    include/minter/api/explorer/explorer_results.h
    include/minter/api/gate/base.h
    include/minter/api/gate/gate_repo.h
    include/minter/api/gate/gate_results.h
    include/minter/api/gate/exchange_calculator.h
    include/minter/api/io_container.h
    include/minter/api/request.h
    )

set(SOURCES
    ${HEADERS}
    src/base_repository.cpp
    src/explorer_results.cpp
    src/explorer_repository.cpp
    src/gate_repository.cpp
    src/explorer/explorer_results.cpp
    src/gate/gate_results.cpp
    src/gate/gate_base.cpp
    src/io_container.cpp
    src/request.cpp
    )
#-header_s arch=x86_64 -header_s build_type=Debug -header_s compiler.runtime=MDd --build=missing
add_library(${PROJECT_NAME} STATIC ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_link_libraries(${PROJECT_NAME} CONAN_PKG::rxcpp)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::cpr)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::libcurl)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::minter_tx)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::toolbox)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::nlohmann_json)
target_link_libraries(${PROJECT_NAME} CONAN_PKG::fmt)

if (ENABLE_TEST)
	# example
	add_executable(liquid_income examples/liquidity_income.cpp)
	target_link_libraries(liquid_income ${PROJECT_NAME})

	include(modules/tests.cmake)
endif ()