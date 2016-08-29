file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testNode ${SRCS})

TARGET_LINK_LIBRARIES(testNode
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testNode 
		COMMAND testNode)

add_dependencies(check testNode)