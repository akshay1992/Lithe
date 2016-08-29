file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testOutputModule ${SRCS})

TARGET_LINK_LIBRARIES(testOutputModule
	lithe_modules
	libgtest
	libgmock
)

add_test(NAME testOutputModule 
		COMMAND testOutputModule)

add_dependencies(check testOutputModule)