cmake_minimum_required(VERSION 2.8)

project(Lithe)

set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")

enable_testing()

add_subdirectory(core)
add_subdirectory(modules)
add_subdirectory(test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(docs ALL
	${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/docs/DoxyFile
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
)
endif(DOXYGEN_FOUND)