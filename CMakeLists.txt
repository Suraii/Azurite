cmake_minimum_required(VERSION 3.10)

# Project name & version
project(Azurite VERSION 0.1)

# C++ Compiler (needed to support modern C++)
set(CMAKE_CXX_COMPILER /bin/clang++)

# Usefull compilation flags
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wextra -Wall")

# C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Conan (library manager) setup
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# Azurite Engine's sources directory
add_subdirectory(engine)

# Unit & functional tests
add_subdirectory(tests)

# Example games made with Azurite
add_subdirectory(examples/shooting_range)

