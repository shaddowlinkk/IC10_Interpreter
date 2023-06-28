//
// Created by natha on 6/25/2023.
//

#ifndef IC10_INTERPRETER_DATA_STRUCTS_H
#define IC10_INTERPRETER_DATA_STRUCTS_H
union _expr;
struct _statement;

typedef struct _env{
    void *device[7];
    int regs[18];
    int stack[512];
}Env;

typedef struct _statement{
    union _expr *expr;
    struct _statement *statement;
}Statement;
#endif //IC10_INTERPRETER_DATA_STRUCTS_H
