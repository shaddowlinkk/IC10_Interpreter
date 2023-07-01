//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_GRAMMER_H
#define IC10_INTERPRETER_GRAMMER_H
#include "Lexer.h"
enum type{
    VAL,
    STRING,
    UNOP,
    BINOP,
    TRIOP,
    QUADOP,
    QUINOP,
    SEXOP
};
union _exprtypes;

struct unop{
    Token *uop;
    union _exprtypes *uout;
    union _exprtypes *uin1;
};
struct binop{
    Token *bop;
    union _exprtypes *bout;
    union _exprtypes *bin1;
    union _exprtypes *bin2;
};
struct triop{
    Token *top;
    union _exprtypes *tout;
    union _exprtypes *tin1;
    union _exprtypes *tin2;
    union _exprtypes *tin3;
};
struct quadop{
    Token *qop;
    union _exprtypes *qout;
    union _exprtypes *qin1;
    union _exprtypes *qin2;
    union _exprtypes *qin3;
    union _exprtypes *qin4;
};
struct quinop{
    Token *quop;
    union _exprtypes *quout;
    union _exprtypes *quin1;
    union _exprtypes *quin2;
    union _exprtypes *quin3;
    union _exprtypes *quin4;
    union _exprtypes *quin5;
};
struct sexop{
    Token *sop;
    union _exprtypes *sout;
    union _exprtypes *sin1;
    union _exprtypes *sin2;
    union _exprtypes *sin3;
    union _exprtypes *sin4;
    union _exprtypes *sin5;
    union _exprtypes *sin6;
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
