file(GLOB_RECURSE lithe_modules_sources ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

# Declare the library
add_library(lithe_modules STATIC ${lithe_modules_sources})

# Link to lithe_core and other dependencies
target_link_libraries(lithe_modules 
	lithe_core
	allocore 
	Gamma 
	portaudio
	# Add any additional dependencies here
)

# Add all subfolders as include directories.
file(GLOB _ALL_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*)
foreach(_FILE ${_ALL_FILES})
  if(IS_DIRECTORY ${_FILE})
    target_include_directories(lithe_modules PUBLIC ${_FILE})
  endif()
endforeach()


file(GLOB_RECURSE lithe_modules_headers ${CMAKE_CURRENT_SOURCE_DIR} *.h)
install( TARGETS lithe_modules DESTINATION lib )
install( FILES ${lithe_modules_headers} DESTINATION include/Lithe/modules )