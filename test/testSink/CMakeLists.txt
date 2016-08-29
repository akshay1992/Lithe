file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testSink ${SRCS})

TARGET_LINK_LIBRARIES(testSink
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testSink 
		COMMAND testSink)

add_dependencies(check testSink)