cmake_minimum_required(VERSION 2.8)

project(Lithe)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

enable_testing()

# Declare the library
file(GLOB lithe_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )
add_library(lithe_core STATIC ${lithe_sources} )
target_include_directories( lithe_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} )

# Install
file(GLOB lithe_headers ${CMAKE_CURRENT_SOURCE_DIR}/Lithe/*.h )
install( TARGETS lithe_core DESTINATION lib )
install( FILES ${lithe_headers} DESTINATION include/Lithe )

# Custom target to build docs
add_subdirectory(docs)

# Custom target to build and run test 
add_subdirectory(test EXCLUDE_FROM_ALL) 
