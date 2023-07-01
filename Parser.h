//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_PARSER_H
#define IC10_INTERPRETER_PARSER_H
#include "Grammer.h"
struct parsetree{
    int lables[512];
    Statement *stmt;
};
#endif //IC10_INTERPRETER_PARSER_H
