file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testParameter ${SRCS})

TARGET_LINK_LIBRARIES(testParameter
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testParameter 
		COMMAND testParameter)

add_dependencies(check testParameter)
