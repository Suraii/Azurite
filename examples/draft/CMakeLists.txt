# Compiling the game from given sources
add_executable(draft main.cpp)

# Linking Azurite Engine's library to the game
target_link_libraries(test PUBLIC azurite_engine)

# Linking Azurite Engine's headers to the game
target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/engine/include)
