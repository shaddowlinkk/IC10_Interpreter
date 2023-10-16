//
// Created by nathan_pc on 10/15/2023.
//

#ifndef IC10_INTERPRETER_EXECUTOR_H
#define IC10_INTERPRETER_EXECUTOR_H
#include "../include/Parser.h"
typedef struct _device{
    unsigned char *name;
    double **slotParams;
    double **deviceParams;
}Device;
typedef struct _enviroment{
    Device **devices;
    double regs[18];
    double stack[512];
    struct parsetree *tree;
}Enviro;
void run(Enviro enviro);
#endif //IC10_INTERPRETER_EXECUTOR_H
