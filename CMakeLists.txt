cmake_minimum_required(VERSION 3.15)

# Project name and version
project(AirRoute-System VERSION 0.1.3 LANGUAGES CXX)

# Specify C/C++ Standard = 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Jump into the src directory to find more CMake instructions
add_subdirectory(src)