//
// Created by natha on 6/25/2023.
//

#ifndef IC10_INTERPRETER_LEXER_H
#define IC10_INTERPRETER_LEXER_H

enum TT_token {
    TT_NEWLINE,
    TT_DPARA,
    TT_BINOP,
    TT_SHIFT,
    TT_BITOP,
    TT_SELECT,
    TT_MOVE,
    TT_JUMP,
    TT_Device,
    TT_RJUMP,
    TT_NUM,
    TT_STRING,
    TT_LABEL,
    TT_REG,
    TT_DEFINE,
    TT_ALIAS,
    TT_MATH,
    TT_SET,
    TT_LOAD,
    TT_SPARA,
    TT_STACK,
    TT_WAIT,
    TT_LOL

};
struct commandToken{
    char *str;
    enum TT_token tokentype;
};

typedef struct _token{
    enum TT_token tokenType;
    char *string;
}Token;
typedef struct _node{
    struct _token *token;
    struct _node *next;
}TokenNode;
TokenNode *Lexer(char *Filename);
#endif //IC10_INTERPRETER_LEXER_H
