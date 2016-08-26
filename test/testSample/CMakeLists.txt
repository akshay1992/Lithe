file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testSample ${SRCS})

TARGET_LINK_LIBRARIES(testSample
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testSample 
		COMMAND testSample)
