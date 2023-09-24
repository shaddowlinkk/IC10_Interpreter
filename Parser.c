//
// Created by natha on 6/30/2023.
//

#include "Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//t
struct parsetree *Parse(TokenNode **tokenlist){
    struct parsetree *out = malloc(sizeof(struct parsetree));
    Statement *start = malloc(sizeof(Statement));
    Statement **parsTracer = &start;
    TokenNode  **listtracer =tokenlist;
    memset(out->lables,-1,512);

    out->stmt=start;
    int lineNum=0;
        while ((*listtracer)){
            switch ((*listtracer)->token->tokenType) {
                case TT_NEWLINE:
                {
                    Statement *new_state = malloc(sizeof(Statement));
                    (*parsTracer)->statement=new_state;
                    parsTracer=&(*parsTracer)->statement;
                }
                    break;
                case TT_DPARA:
                    break;
                case TT_HASH:
                    break;
                case TT_BINOP:
                    break;
                case TT_SHIFT:
                    break;
                case TT_BITOP:
                    break;
                case TT_SELECT:
                    break;
                case TT_MOVE:
                    break;
                case TT_JUMP:
                    break;
                case TT_DEVICE:
                    break;
                case TT_DEVICE_CON:
                    break;
                case TT_RJUMP:
                    break;
                case TT_NUM:
                    break;
                case TT_STRING:
                    break;
                case TT_LABEL:
                    break;
                case TT_REG:
                    break;
                case TT_DEFINE:
                    break;
                case TT_ALIAS:
                    break;
                case TT_MATH:
                    break;
                case TT_SET:
                    break;
                case TT_LOAD:
                    break;
                case TT_SPARA:
                    break;
                case TT_STACK:
                    break;
                case TT_WAIT:
                    break;
                case TT_LOL:
                    break;
                case TT_MISC:
                    break;
            }
        }
        listtracer=&(*listtracer)->next;
}
