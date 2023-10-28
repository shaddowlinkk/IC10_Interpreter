//
// Created by natha on 6/25/2023.
//

#include "tokenlist.h"
#ifndef IC10_INTERPRETER_LEXER_H
#define IC10_INTERPRETER_LEXER_H

typedef struct _token{
    enum type OP_type;
    enum TT_token tokenType;
    char *string;
}Token;
typedef struct _node{
    struct _token *token;
    struct _node *next;
}TokenNode;
TokenNode *Lexer(char *Filename);
void printlex(TokenNode *list);
#endif //IC10_INTERPRETER_LEXER_H
