file(GLOB lithe_modules_SRCS
	*.h *.cpp
)

# Declare the library
add_library(lithe_modules STATIC
    ${lithe_modules_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(lithe_modules PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)