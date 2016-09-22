file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testAtlas ${SRCS})

TARGET_LINK_LIBRARIES(testAtlas
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testAtlas 
		COMMAND testAtlas)

add_dependencies(check testAtlas)
