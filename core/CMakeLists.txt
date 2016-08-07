add_subdirectory(allocore-build)

file(GLOB lithe_core_SRCS
	*.h *.cpp
)

# Declare the library
add_library(lithe_core STATIC
	${lithe_core_SRCS}
)

# Link to allocore
target_link_libraries(lithe_core allocore)

# Specify here the include directories exported
# by this library
target_include_directories(lithe_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)