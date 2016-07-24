file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testDummy ${SRCS})

TARGET_LINK_LIBRARIES(testDummy
	lithe_modules
	libgtest
	libgmock
)

add_test(NAME testDummy
		COMMAND testDummy)