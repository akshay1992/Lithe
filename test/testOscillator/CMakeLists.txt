file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testOscillator ${SRCS})

TARGET_LINK_LIBRARIES(testOscillator
	lithe_modules
	libgtest
	libgmock
)

add_test(NAME testOscillator 
		COMMAND testOscillator)
