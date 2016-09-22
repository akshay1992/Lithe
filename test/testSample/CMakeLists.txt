file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testSample ${SRCS})

TARGET_LINK_LIBRARIES(testSample
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testSample 
		COMMAND testSample)

add_dependencies(check testSample)