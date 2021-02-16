# Azurite Engine's compilation as a dynamic library
add_library(azurite_engine SHARED
src/Game.cpp
src/StateMachine.cpp
src/ComponentsStorage.cpp
src/SystemsManager.cpp
src/Snitch.cpp
src/lib.cpp
src/modules/SfmlModule.cpp
src/systems/SpriteSystems.cpp
src/systems/LifeSystems.cpp
src/systems/UISystems.cpp
src/systems/MovementSystems.cpp
src/systems/SoundSystems.cpp
)

# Linking inner headers to the lib, hopefully this will be replaced by module partitions with gcc 11
target_include_directories(azurite_engine PUBLIC
${PROJECT_SOURCE_DIR}/engine/include
)

# Linking SFML library to the lib
target_link_libraries(azurite_engine PUBLIC ${CONAN_LIBS})
