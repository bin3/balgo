add_subdirectory(balgo)
add_subdirectory(main)

install(DIRECTORY balgo/ DESTINATION include/balgo FILES_MATCHING PATTERN "*.h")
