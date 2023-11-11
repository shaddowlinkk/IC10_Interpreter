//
// Created by nathan_pc on 10/15/2023.
//

#ifndef IC10_INTERPRETER_EXECUTOR_H
#define IC10_INTERPRETER_EXECUTOR_H
#include "readEnviroment.h"
double getRegisterData(const char *token,Enviro *env,struct parsedata *pdata);
void execute_stmt(Statement **trace,Enviro *env,struct parsedata *pdata);
#endif //IC10_INTERPRETER_EXECUTOR_H
