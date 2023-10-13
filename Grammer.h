//
// Created by natha on 6/30/2023.
//

#ifndef IC10_INTERPRETER_GRAMMER_H
#define IC10_INTERPRETER_GRAMMER_H
#include "Lexer.h"

union _exprtypes;

struct cmd{
    Token *cop;
    Token *cin1;
};

struct unop{
    Token *uop;
    Token *uout;
    Token *uin1;
};
struct binop{
    Token *bop;
    Token *bout;
    Token *bin1;
    Token *bin2;
};
struct triop{
    Token *top;
    Token *tout;
    Token *tin1;
    Token *tin2;
    Token *tin3;
};
struct quadop{
    Token *qop;
    Token *qout;
    Token *qin1;
    Token *qin2;
    Token *qin3;
    Token *qin4;
};
struct quinop{
    Token *quop;
    Token *quout;
    Token *quin1;
    Token *quin2;
    Token *quin3;
    Token *quin4;
    Token *quin5;
};
struct sexop{
    Token *sop;
    Token *sout;
    Token *sin1;
    Token *sin2;
    Token *sin3;
    Token *sin4;
    Token *sin5;
    Token *sin6;
};

union _exprtypes{
    struct cmd *cmd;
    struct unop *unop;
    struct binop *binop;
    struct triop *triop;
    struct quadop *quadop;
    struct quinop *quinop;
    struct sexop *sexop;
};
typedef struct _expr{
    enum type type;
    union _exprtypes *expr;
}Exper;

typedef struct _statement{
    struct _expr *stm_expr;
    struct _statement *statement;
    struct _statement *back;
}Statement;
#endif //IC10_INTERPRETER_GRAMMER_H
