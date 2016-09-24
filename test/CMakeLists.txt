# ------------------------------------------------------------

if( NOT TARGET libgtest)

    # We need thread support
    find_package(Threads REQUIRED)

    # Enable ExternalProject CMake module
    include(ExternalProject)

    # Download and install GoogleTest
    ExternalProject_Add(
        gtest
        URL https://github.com/google/googletest/archive/master.zip
        PREFIX ${CMAKE_BINARY_DIR}/gtest
        # Disable install step
        INSTALL_COMMAND ""
    )

    # Get GTest source and binary directories from CMake project
    ExternalProject_Get_Property(gtest source_dir binary_dir)

    # Create a libgtest target to be used as a dependency by test programs
    add_library(libgtest IMPORTED STATIC GLOBAL)
    add_dependencies(libgtest gtest)

    # Set libgtest properties
    set_target_properties(libgtest PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )

    # Create a libgmock target to be used as a dependency by test programs
    add_library(libgmock IMPORTED STATIC GLOBAL)
    add_dependencies(libgmock gtest)

    # Set libgmock properties
    set_target_properties(libgmock PROPERTIES
        "IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
        "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
    )

    # I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
    include_directories("${source_dir}/googletest/include"
                        "${source_dir}/googlemock/include")

endif()

# ------------------------------------------------------------

# Custom target for building and running tests
if( NOT TARGET check)
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND})
endif()

# Adding the tests individually here

add_subdirectory(testOutlet)
add_subdirectory(testInlet)
add_subdirectory(testNode)
add_subdirectory(testSink)
add_subdirectory(testSorter)
add_subdirectory(testSample)
add_subdirectory(testAtlas)
add_subdirectory(testParameterField)
add_subdirectory(testParameter)
