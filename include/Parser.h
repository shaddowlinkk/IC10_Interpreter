//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_PARSER_H
#define IC10_INTERPRETER_PARSER_H
#include "Grammer.h"
#include "Util.h"
#define REDEF_SIZE 128

struct parsedata{
    Key *lables[512];//item type statment
    Key *redef[128];
    int lines;
    Statement *line_table;
    Statement *stmt;
    Statement **trace;
};
struct parsedata *Parse(TokenNode **tokenlist);
void printTree(struct parsedata *tree);
#endif //IC10_INTERPRETER_PARSER_H
