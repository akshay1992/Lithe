file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testInlet ${SRCS})

TARGET_LINK_LIBRARIES(testInlet
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testInlet 
		COMMAND testInlet)
