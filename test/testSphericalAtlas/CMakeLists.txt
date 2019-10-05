file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testSphericalAtlas ${SRCS})

TARGET_LINK_LIBRARIES(testSphericalAtlas
	lithe_core
	gtest_main
)

add_test(NAME testSphericalAtlas 
		COMMAND testSphericalAtlas)

add_dependencies(check testSphericalAtlas)
