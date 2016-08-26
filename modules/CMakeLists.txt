file(GLOB lithe_modules_folders ${CMAKE_CURRENT_SOURCE_DIR}/*/)

file(GLOB lithe_modules_sources ${lithe_modules_folders}/*.cpp)

# Declare the library
add_library(lithe_modules STATIC
    ${lithe_modules_sources}
)

add_subdirectory(OutputModule)
add_subdirectory(Oscillator)

# Link to allocore
target_link_libraries(lithe_modules lithe_core Gamma)

# Specify here the include directories exported
# by this library
# target_include_directories(lithe_modules PUBLIC
#     ${lithe_modules_folders}
# )