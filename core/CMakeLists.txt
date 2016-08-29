file(GLOB lithe_core_sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp )

# Declare the library
add_library(lithe_core STATIC ${lithe_core_sources} )

target_include_directories( lithe_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )

file(GLOB_RECURSE lithe_core_headers ${CMAKE_CURRENT_SOURCE_DIR} *.h )
install( TARGETS lithe_core DESTINATION lib )
install( FILES ${lithe_core_headers} DESTINATION include/Lithe/core )