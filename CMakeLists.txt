cmake_minimum_required(VERSION 3.17)
project(c_bf C)

set(CMAKE_C_STANDARD 11)

add_executable(c_bf src/main.c src/tape.h src/tape.c)