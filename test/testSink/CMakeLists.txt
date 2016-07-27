file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testSink ${SRCS})

target_link_libraries(testSink
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testSink 
		COMMAND testSink)
