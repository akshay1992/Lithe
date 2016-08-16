# Install allocore using the shell script
execute_process(
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMAND "./install.sh"
    RESULT_VARIABLE rv
	)

