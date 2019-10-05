# Custom target for building and running tests
if( NOT TARGET check)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
endif()

# Glob for the test sources
file(GLOB TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/**/*.cpp)

# Remote the template test (used as a shorthand generate a new test folder)
list(REMOVE_ITEM TEST_SRCS ${CMAKE_CURRENT_SOURCE_DIR}/testTemplate/testTemplate.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(lithe_testrunner ${TEST_SRCS})

TARGET_LINK_LIBRARIES(lithe_testrunner
	PUBLIC
	lithe_core
	gtest_main
)

add_test(NAME lithe_testrunner 
		COMMAND lithe_testrunner)

add_dependencies(check lithe_testrunner)