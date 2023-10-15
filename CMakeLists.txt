cmake_minimum_required(VERSION 3.24)
project(IC10_Interpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(IC10_Interpreter src/main.c include/Data_structs.h src/Lexer.c include/Lexer.h include/tokenlist.h src/Parser.c include/Parser.h include/Grammer.h
        src/Util.c
        include/Util.h)
