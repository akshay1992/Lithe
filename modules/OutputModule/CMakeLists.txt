# Specify any dependencies
# target_link_libraries(lithe_modules ??)

# Add sources files
file(GLOB srcs ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
target_sources(lithe_modules PUBLIC ${srcs})


# Add this directory as an include directory
target_include_directories(lithe_modules PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)