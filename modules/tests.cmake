if (APPLE)
	add_definitions(-DGTEST_USE_OWN_TR1_TUPLE)
	add_definitions(-D__GLIBCXX__)
endif ()

enable_testing()
add_definitions(-DMINTER_API_TESTING=1)

add_executable(${PROJECT_NAME}-test
               tests/main.cpp
               tests/explorer_test.cpp)

if (ENABLE_PVS)
	include(PVS-Studio)
	pvs_studio_add_target(TARGET ${PROJECT_NAME}.analyze ALL
	                      OUTPUT FORMAT errorfile
	                      CONFIG ${CMAKE_CURRENT_SOURCE_DIR}/pvs.cfg
	                      ANALYZE ${PROJECT_NAME}-test
	                      SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/include
	                      LOG target.err)
endif ()

if (NOT MSVC)
	target_compile_options(${PROJECT_NAME}-test PRIVATE -Wno-missing-field-initializers)
endif ()
target_link_libraries(${PROJECT_NAME}-test CONAN_PKG::gtest)
target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})

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
	include(modules/CodeCoverage.cmake)
	append_coverage_compiler_flags()
	setup_target_for_coverage_lcov(
		NAME ${PROJECT_NAME}-coverage
		EXECUTABLE ${PROJECT_NAME}-test
		DEPENDENCIES ${PROJECT_NAME}-test
	)
endif ()

add_test(NAME test-all COMMAND ${CMAKE_CURRENT_BINARY_DIR}/bin/${PROJECT_NAME}-test)