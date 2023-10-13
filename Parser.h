//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_PARSER_H
#define IC10_INTERPRETER_PARSER_H
#include "Grammer.h"
struct parsetree{
    int lables[512];//<--needs to be a map
    Statement *stmt;
};
struct parsetree *Parse(TokenNode **tokenlist);
void printTree(struct parsetree *tree);
#endif //IC10_INTERPRETER_PARSER_H
