file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testOutlet ${SRCS})

TARGET_LINK_LIBRARIES(testOutlet
	lithe_core
	gtest_main
)

add_test(NAME testOutlet 
		COMMAND testOutlet)

add_dependencies(check testOutlet)