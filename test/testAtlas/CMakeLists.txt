file(GLOB SRCS *.cpp)

ADD_EXECUTABLE(testAtlas ${SRCS})

TARGET_LINK_LIBRARIES(testAtlas
	lithe_core
	libgtest
	libgmock
)

add_test(NAME testAtlas 
		COMMAND testAtlas)

add_dependencies(check testAtlas)
