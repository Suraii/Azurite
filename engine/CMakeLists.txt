# Azurite Engine's compilation as a dynamic library
add_library(azurite_engine SHARED
src/Game.cpp
src/lib.cpp
)

# Linking inner headers to the lib, hopefully this will be replaced by module partitions with gcc 11
target_include_directories(azurite_engine PUBLIC
${PROJECT_SOURCE_DIR}/engine/include
)
