cmake_minimum_required(VERSION 3.24)
project(IC10_Interpreter C)

set(CMAKE_C_STANDARD 99)

add_executable(IC10_Interpreter src/main.c src/Lexer.c include/Lexer.h include/tokenlist.h src/Parser.c include/Parser.h include/Grammer.h
        src/Util.c
        include/Util.h
        src/executor.c
        include/executor.h
        src/readEnviroment.c
        include/readEnviroment.h
        src/tui.c
        include/tui.h
        src/debug.c
        include/debug.h
)
