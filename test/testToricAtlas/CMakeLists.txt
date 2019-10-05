file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testToricAtlas ${SRCS})

TARGET_LINK_LIBRARIES(testToricAtlas
	lithe_core
	gtest_main
)

add_test(NAME testToricAtlas 
		COMMAND testToricAtlas)

add_dependencies(check testToricAtlas)
