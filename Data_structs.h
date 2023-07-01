//
// Created by natha on 6/25/2023.
//

#ifndef IC10_INTERPRETER_DATA_STRUCTS_H
#define IC10_INTERPRETER_DATA_STRUCTS_H


typedef struct _env{
    void *device[7];
    int regs[18];
    int stack[512];
}Env;
#endif //IC10_INTERPRETER_DATA_STRUCTS_H
