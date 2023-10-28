//
// Created by nathan_pc on 10/15/2023.
//

#ifndef IC10_INTERPRETER_EXECUTOR_H
#define IC10_INTERPRETER_EXECUTOR_H
#include "../include/Parser.h"
struct slotdata{

};
struct slotnode{
    int slotNum;
};
typedef struct _device{
    char *name;
    int name_size;
    Key **deviceSettings; // item type double
    Key **slotParams;// item type double
    Key **deviceParams;// item type double
}Device;
typedef struct _enviroment{
    Device **devices;
    int numdevs;
    double regs[18];
    double stack[512];
    struct parsetree *tree;
}Enviro;
void run(Enviro enviro);
#endif //IC10_INTERPRETER_EXECUTOR_H
