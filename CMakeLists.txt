cmake_minimum_required(VERSION 3.10)
# Project name.
project(market_simulation)

# Set the C++ standard.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Headers + source files.
include_directories(include)
include_directories(include/parser)
file(GLOB SOURCES "src/*.cpp")
file(GLOB PARSER_SOURCES "src/parser/*.cpp")

# Executable.
add_executable(simulation ${SOURCES} ${PARSER_SOURCES} example/example1.cpp)

# Output path.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)