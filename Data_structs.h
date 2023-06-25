//
// Created by natha on 6/25/2023.
//

#ifndef IC10_INTERPRETER_DATA_STRUCTS_H
#define IC10_INTERPRETER_DATA_STRUCTS_H
union _expr;
typedef struct _env{
    double regs[18];
    double stack[512];
    union _expr *code[128];
}Env;

typedef struct _statement{

    union _expr *expr
}Statement;
#endif //IC10_INTERPRETER_DATA_STRUCTS_H
