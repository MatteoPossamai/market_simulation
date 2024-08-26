cmake_minimum_required(VERSION 3.10)
# Project name.
project(market_simulation)

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall")

# Headers + source files.
include_directories(include)
file(GLOB SOURCES "src/*.cpp")

# Executable.
add_executable(simulation_exec ${SOURCES} ${PARSER_SOURCES} example/example1.cpp)

# Output path.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)