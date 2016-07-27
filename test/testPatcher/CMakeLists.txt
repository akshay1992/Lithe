file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testPatcher ${SRCS})

TARGET_LINK_LIBRARIES(testPatcher
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testPatcher 
		COMMAND testPatcher)