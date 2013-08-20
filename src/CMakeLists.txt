add_subdirectory(balgo)

install(DIRECTORY balgo/ DESTINATION include/balgo FILES_MATCHING PATTERN "*.h")
