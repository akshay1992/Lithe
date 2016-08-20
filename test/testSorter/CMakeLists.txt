file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testSorter ${SRCS})

TARGET_LINK_LIBRARIES(testSorter
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testSorter 
		COMMAND testSorter)
