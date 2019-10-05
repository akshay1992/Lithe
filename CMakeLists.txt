cmake_minimum_required(VERSION 2.8.2)

project(Lithe 
		LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++11")

# Declare the library
file(GLOB lithe_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_library(lithe_core STATIC ${lithe_sources} )
target_include_directories( lithe_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

# Install
file(GLOB lithe_headers ${CMAKE_CURRENT_SOURCE_DIR}/Lithe/*.h )
install( TARGETS lithe_core DESTINATION lib )
install( FILES ${lithe_headers} DESTINATION include/Lithe )

# If this is built as a git submodule to LitheModules, then ignore the test cases and docs. 
if(LITHE_DONT_BUILD_TESTS)
	message("-- Ignoring docs & test targets for Lithe")

else()
	message("-- Setting up docs target for Lithe")

	# Pull the integration code that builds gtest
	include(cmake/gtest-integration.cmake)

	# Custom target to build docs
	add_subdirectory(docs)

	message("-- Setting up test target for Lithe")
	# Custom target to build and run test 
	add_subdirectory(test EXCLUDE_FROM_ALL) 
endif()
