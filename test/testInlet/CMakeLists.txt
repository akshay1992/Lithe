file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testInlet ${SRCS})

TARGET_LINK_LIBRARIES(testInlet
	lithe_core
	gtest_main
)

add_test(NAME testInlet 
		COMMAND testInlet)

add_dependencies(check testInlet)