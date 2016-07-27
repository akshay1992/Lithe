file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testTemplate ${SRCS})

TARGET_LINK_LIBRARIES(testTemplate
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testTemplate 
		COMMAND testTemplate)