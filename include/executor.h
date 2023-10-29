//
// Created by nathan_pc on 10/15/2023.
//

#ifndef IC10_INTERPRETER_EXECUTOR_H
#define IC10_INTERPRETER_EXECUTOR_H
#include "../include/Parser.h"
struct slotdata{
    char *name;
    int datasize;
    char *data;
    struct slotdata *next;
};
struct slotnode{
    int slotNum;
    struct slotdata *start;
    struct slotnode *next;
};
typedef struct _device{
    char *name;
    int name_size;
    int device_num;
    int num_slots;
    Key **deviceSettings; // item type double
    struct slotnode *slotParams;// item type double
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
