file(GLOB SRCS *.cpp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

ADD_EXECUTABLE(testParameterField ${SRCS})

TARGET_LINK_LIBRARIES(testParameterField
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testParameterField 
		COMMAND testParameterField)

add_dependencies(check testParameterField)
