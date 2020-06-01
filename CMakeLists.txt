cmake_minimum_required(VERSION 3.8)
PROJECT(rudis)
add_definitions(-std=c++14)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(header)
aux_source_directory(src/commands R_COMMANDS)
aux_source_directory(src/common R_COMMON)
aux_source_directory(src/objects R_OBJECTS)
aux_source_directory(src/server R_SERVER)

add_executable(main src/main.cc ${R_SERVER} ${R_OBJECTS} ${R_COMMON} ${R_COMMANDS})
add_executable(test_echo tests/test_echo.cc ${R_SERVER} ${R_OBJECTS} ${R_COMMON} ${R_COMMANDS})