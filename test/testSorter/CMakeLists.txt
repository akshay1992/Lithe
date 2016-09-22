file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testSorter ${SRCS})

TARGET_LINK_LIBRARIES(testSorter
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testSorter 
		COMMAND testSorter)

add_dependencies(check testSorter)