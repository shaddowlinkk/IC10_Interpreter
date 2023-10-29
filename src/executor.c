//
// Created by nathan_pc on 10/15/2023.
//

#include "../include/executor.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
enum TT_token getTokenType(struct _expr *expr){
    switch (expr->type) {
        case UNOP:
            return expr->expr->unop->uop->tokenType;
        case BINOP:
            return expr->expr->binop->bop->tokenType;
        case TRIOP:
            return expr->expr->triop->top->tokenType;
        case QUADOP:
            return expr->expr->quadop->qop->tokenType;
        case QUINOP:
            return expr->expr->quinop->quop->tokenType;
        case SEXOP:
            return expr->expr->sexop->sop->tokenType;
        case CMD:
            return expr->expr->cmd->cop->tokenType;
        default:
            return -1;
    }
}
/**
 * this function is used to execute one statement on provided environment
 * @param trace
 * @param env
 * @param start
 */
void execute_stmt(Statement **trace,Enviro *env,struct parsedata *pdata){
    if((*trace)->stm_expr->type!=LABEL) {
        switch (getTokenType((*trace)->stm_expr)) {
            case TT_BINOP:{
                if(){
                }
                break;
            }
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
            case TT_RJUMP:
                break;
            case TT_MATH:
                break;
            case TT_SET:
                break;
            case TT_LOAD:
                break;
            case TT_STACK:
                break;
            case TT_WAIT:
                break;
            default:
                break;
        }
    }
}


/**
 * This function will execute a full parse tree using the provided environment data.
 * @param start the parse tree that is to be executed
 * @param env the environment that the parse tree should use for data
 */
void execute(struct parsedata *pdata, Enviro *env){
    Statement **stmt_Tracer =&pdata->stmt;
    while (*stmt_Tracer){

    }
}
