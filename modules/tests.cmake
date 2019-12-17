set(gtest_force_shared_crt ${ENABLE_SHARED} CACHE BOOL "" FORCE)
add_definitions(-DTEST_ROOT="${CMAKE_CURRENT_SOURCE_DIR}/tests")
set(PROJECT_NAME_TEST ${PROJECT_NAME}-test)

if (APPLE)
	add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
	add_definitions(-D__GLIBCXX__)
endif ()
if (MSVC)
	string(REGEX REPLACE "\\/W4" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
endif ()

set(TEST_SOURCES
    tests/main.cpp
    tests/explorer_test.cpp)

add_executable(${PROJECT_NAME_TEST} ${TEST_SOURCES})
if (NOT MSVC)
	target_compile_options(${PROJECT_NAME_TEST} PUBLIC -Wno-unused-parameter)
endif ()
target_include_directories(${PROJECT_NAME_TEST} PRIVATE tests)
target_link_libraries(${PROJECT_NAME_TEST} PRIVATE CONAN_PKG::gtest)
target_link_libraries(${PROJECT_NAME_TEST} PUBLIC ${PROJECT_NAME})


if (WITH_COVERAGE)
	set(COVERAGE_LCOV_EXCLUDES
	    'libs/*'
	    '/usr/include/*'
	    'tests/*'
	    'boost/*'
	    '/usr/include/*'
	    '/usr/local/*'
	    'v1'
	    '4.9'
	    )
	include(CodeCoverage.cmake)
	append_coverage_compiler_flags()
	setup_target_for_coverage_lcov(
		NAME ${PROJECT_NAME_TEST}-coverage
		EXECUTABLE ${PROJECT_NAME_TEST}
		DEPENDENCIES ${PROJECT_NAME}
	)
endif ()