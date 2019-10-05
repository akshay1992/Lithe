cmake_minimum_required(VERSION 2.8.2)

#-----------------------------------------------------------------
#                  DEFAULT FLAGS 
#-----------------------------------------------------------------
if (NOT DEFINED LITHE_TESTS)
	set(LITHE_TESTS FALSE)
endif()

# Print all the flags

message(STATUS "LITHE_TESTS -- ${LITHE_TESTS}")

#-----------------------------------------------------------------
#                  CONFIGURE LITHE 
#-----------------------------------------------------------------

project(Lithe LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "-std=c++11")

# Declare the library
file(GLOB lithe_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_library(lithe_core STATIC ${lithe_sources} )
target_include_directories( lithe_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

# Install
file(GLOB lithe_headers ${CMAKE_CURRENT_SOURCE_DIR}/Lithe/*.h )
install( TARGETS lithe_core DESTINATION lib )
install( FILES ${lithe_headers} DESTINATION include/Lithe )

#-----------------------------------------------------------------
#             CONFIGURE DOXYGEN DOCUMENTATION 
#-----------------------------------------------------------------

# Custom target to build docs
add_subdirectory(docs EXCLUDE_FROM_ALL)

#-----------------------------------------------------------------
#             CONFIGURE LITHE UNIT TESTS 
#-----------------------------------------------------------------

if(LITHE_TESTS)
	message(STATUS "Setting up test target for Lithe")

	# Pull the integration code that builds gtest
	include(cmake/gtest-integration.cmake)

	# Custom target to build and run test 
	add_subdirectory(test EXCLUDE_FROM_ALL) 
	message(STATUS "Setting up test target for Lithe (done)")
endif()
