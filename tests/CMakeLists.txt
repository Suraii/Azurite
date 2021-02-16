# Compiling the tests main
add_executable(engine_core_tests engine_core_tests.cpp)

# Linking Azurite Engine's library to the tests executable
target_link_libraries(engine_core_tests PUBLIC azurite_engine)

# Linking Test library to the texts executable
target_link_libraries(engine_core_tests PUBLIC ${CONAN_LIBS_BOOST})

# Linking Azurite Engine's headers to the tests executable
target_include_directories(engine_core_tests PUBLIC ${PROJECT_SOURCE_DIR}/engine/include)

