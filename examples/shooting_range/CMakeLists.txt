# Compiling the game from given sources
add_executable(shooting_range main.cpp
states/MainState.cpp
states/GameState.cpp
states/PauseState.cpp
states/ScoreState.cpp
systems/ShootingRangeSystems.cpp
)

# Linking Azurite Engine's library to the game
target_link_libraries(shooting_range PUBLIC azurite_engine)

# Linking Azurite Engine's headers to the game
target_include_directories(shooting_range PUBLIC ${PROJECT_SOURCE_DIR}/engine/include
PUBLIC .)
