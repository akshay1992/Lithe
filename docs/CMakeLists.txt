find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(docs ALL
	${DOXYGEN_EXECUTABLE} ${PROJECT_SOURCE_DIR}/docs/DoxyFile
	WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/docs
)
endif(DOXYGEN_FOUND)