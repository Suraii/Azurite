cmake_minimum_required(VERSION 3.10)

# Project name & version
project(Azurite VERSION 0.1)

# C++ Standards
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# DEV cmake test executable
add_executable(test src/test_main.cpp)
