cmake_minimum_required(VERSION 3.8)
project(Coding)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES HeuristicLib2.c HeuristicTest.c)
add_executable(Coding ${SOURCE_FILES})