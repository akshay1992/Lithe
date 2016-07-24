file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testBlock ${SRCS})

TARGET_LINK_LIBRARIES(testBlock
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testBlock 
		COMMAND testBlock)