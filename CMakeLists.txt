cmake_minimum_required(VERSION 3.24)
project(IC10_Interpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(IC10_Interpreter main.c Data_structs.h Lexer.c Lexer.h tokenlist.h Parser.c Parser.h Grammer.h)
