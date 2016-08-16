cmake_minimum_required(VERSION 2.8)

project(Lithe)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

enable_testing()

add_subdirectory(allocore-build)
add_subdirectory(core)
# add_subdirectory(modules)
add_subdirectory(test)
add_subdirectory(docs)