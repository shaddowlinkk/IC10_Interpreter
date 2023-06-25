cmake_minimum_required(VERSION 3.24)
project(IC10_Interpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(IC10_Interpreter main.c Data_structs.h cmake-build-debug/Lexer.c cmake-build-debug/Lexer.h)
