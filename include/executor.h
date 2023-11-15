//
// Created by nathan_pc on 10/15/2023.
//

#ifndef IC10_INTERPRETER_EXECUTOR_H
#define IC10_INTERPRETER_EXECUTOR_H
#include "readEnviroment.h"
double getRegisterData(const char *token,Enviro *env,struct parsedata *pdata);
void execute_stmt(Enviro *env,struct parsedata *pdata);
int checkForDeviceConnected(Enviro *env,int devNum);
#endif //IC10_INTERPRETER_EXECUTOR_H
