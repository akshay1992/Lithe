cmake_minimum_required(VERSION 2.8)

project(Lithe)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

enable_testing()

add_subdirectory(core)
add_subdirectory(modules)

# Custom target to build docs
add_subdirectory(docs)

# Custom target to build and run test 
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
add_subdirectory(test EXCLUDE_FROM_ALL) 

install(FILES Lithe.h DESTINATION include/Lithe)