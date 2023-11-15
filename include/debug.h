//
// Created by nathan_pc on 11/2/2023.
//

#ifndef IC10_INTERPRETER_DEBUG_H
#define IC10_INTERPRETER_DEBUG_H

#include "readEnviroment.h"

struct devicelist{
    char *DeviceSetting[512];
    char *Deviceparam[512];
    struct devicelist *next;
};

typedef struct _debug{
    struct devicelist *lists;
}Debug;
void getKeysEnv(Enviro *env,Debug *out);
void printRegisters(Enviro *env);
#endif //IC10_INTERPRETER_DEBUG_H
