//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_PARSER_H
#define IC10_INTERPRETER_PARSER_H
#include "Grammer.h"
#include "Util.h"
struct parsetree{
    Key *lables[512];//item type statment
    int lines;
    Statement *line_table;
    Statement *stmt;
};
struct parsetree *Parse(TokenNode **tokenlist);
void printTree(struct parsetree *tree);
#endif //IC10_INTERPRETER_PARSER_H
