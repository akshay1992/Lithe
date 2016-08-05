file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testTerminal ${SRCS})

TARGET_LINK_LIBRARIES(testTerminal
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testTerminal 
		COMMAND testTerminal)
