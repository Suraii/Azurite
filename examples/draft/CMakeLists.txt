# Compiling the game from given sources
add_executable(draft main.cpp
states/MainState.cpp
states/GameState.cpp
states/PauseState.cpp
systems/ShootingRangeSystems.cpp
)

# Linking Azurite Engine's library to the game
target_link_libraries(draft PUBLIC azurite_engine)

# Linking Azurite Engine's headers to the game
target_include_directories(draft PUBLIC ${PROJECT_SOURCE_DIR}/engine/include
PUBLIC .)
