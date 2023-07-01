//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_GRAMMER_H
#define IC10_INTERPRETER_GRAMMER_H
#include "Lexer.h"
enum type{
    VAL,
    STRING,
    UNOP;
    BINOP;
    TRIOP;
    QUADOP;
    QUINOP;
    SEXOP;
};
union _exprtypes;

struct unop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
};
struct binop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
    union _exprtypes in2;
};
struct trinop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
    union _exprtypes in2;
    union _exprtypes in3;
};
struct triop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
    union _exprtypes in2;
    union _exprtypes in3;
};
struct quadop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
    union _exprtypes in2;
    union _exprtypes in3;
    union _exprtypes in4;
};
struct quinop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
    union _exprtypes in2;
    union _exprtypes in3;
    union _exprtypes in4;
    union _exprtypes in5;
};
struct sexop{
    Token *op;
    union _exprtypes out;
    union _exprtypes in1;
    union _exprtypes in2;
    union _exprtypes in3;
    union _exprtypes in4;
    union _exprtypes in5;
    union _exprtypes in6;
};

union _exprtypes{
    int val;
    char *string;
    struct unop;
    struct binop;
    struct triop;
    struct quadop;
    struct quinop;
    struct sexop;
};
typedef struct _expr{
    enum type type;
    union _exprtypes expr;
}Exper;

typedef struct _statement{
    struct _expr *expr;
    struct _statement *statement;
}Statement;
#endif //IC10_INTERPRETER_GRAMMER_H
