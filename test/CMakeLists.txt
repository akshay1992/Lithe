# Custom target for building and running tests
if( NOT TARGET check)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
endif()

# Adding the tests individually here

add_subdirectory(testOutlet)
add_subdirectory(testInlet)
add_subdirectory(testNode)
add_subdirectory(testSorter)
add_subdirectory(testSample)
add_subdirectory(testSphericalAtlas)
add_subdirectory(testToricAtlas)