//
// Created by nathan_pc on 10/15/2023.
//

#include "../include/executor.h"
#include "../include/parser.h"
#include "../include/readEnviroment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
enum Commands getTokenType(struct _expr *expr){
    switch (expr->type) {
        case UNOP:
            return expr->expr->unop->uop->command;
        case BINOP:
            return expr->expr->binop->bop->command;
        case TRIOP:
            return expr->expr->triop->top->command;
        case QUADOP:
            return expr->expr->quadop->qop->command;
        case QUINOP:
            return expr->expr->quinop->quop->command;
        case SEXOP:
            return expr->expr->sexop->sop->command;
        case CMD:
            return expr->expr->cmd->cop->command;
        default:
            return -1;
    }
}
double getRegisterData(const char *token,Enviro *env){
    //can be optimized useing pointer arithmatic
    double data;
    int len = (int)strlen(token);
    if(token[0]=='r'&&token[1]=='r'){
        char *tmp = malloc(len-1);
        strncpy(tmp,&token[1],len-1);
        data=floor(env->regs[(int)floor(getRegisterData(tmp,env))]);
        return data;
    }else if((token[1]>='0'&&token[1]<='9')){
        int idx= strtol(&token[1],NULL,0);
        data=floor(env->regs[idx]);
        return data;
    }else{
        return strtol(&token[0],NULL,0);
    }
}
/**
 * this function is used to execute one statement on provided environment
 * @param trace the pointer to a pointer that is the statement that you want to execute
 * @param env the environment that you want to execute agents
 * @param pdata the parsed data which includes labels and redefinitions
 */
void execute_stmt(Statement **trace,Enviro *env,struct parsedata *pdata){
    if((*trace)->stm_expr->type!=LABEL) {
        switch (getTokenType((*trace)->stm_expr)) {
            case ABS:{
                double in1=0;
                if((*trace)->stm_expr->expr->unop->uin1->tokenType == TT_NUM || (*trace)->stm_expr->expr->unop->uin1->tokenType == TT_REG){
                    in1=((*trace)->stm_expr->expr->unop->uin1->tokenType == TT_NUM)?
                            strtod((*trace)->stm_expr->expr->unop->uin1->string,NULL):
                            getRegisterData((*trace)->stm_expr->expr->unop->uin1->string,env);
                    env->regs[(int)getRegisterData((*trace)->stm_expr->expr->unop->uout->string+1,env)]= abs((int)in1);
                }else{
                }
                break;
            }
            case ACOS:
                break;
            case ADD:
                break;
            case AND:
                break;
            case ASIN:
                break;
            case ATAN:
                break;
            case ATAN2:
                break;
            case BAP:
                break;
            case BAPAL:
                break;
            case BAPZ:
                break;
            case BAPZAL:
                break;
            case BDNS:
                break;
            case BDNSAL:
                break;
            case BDSE:
                break;
            case BDSEAL:
                break;
            case BEQ:
                break;
            case BEQAL:
                break;
            case BEQZ:
                break;
            case BEQZAL:
                break;
            case BGE:
                break;
            case BGEAL:
                break;
            case BGEZ:
                break;
            case BGEZAL:
                break;
            case BGT:
                break;
            case BGTAL:
                break;
            case BGTZ:
                break;
            case BGTZAL:
                break;
            case BLE:
                break;
            case BLEAL:
                break;
            case BLEZ:
                break;
            case BLEZAL:
                break;
            case BLT:
                break;
            case BLTAL:
                break;
            case BLTZ:
                break;
            case BLTZAL:
                break;
            case BNA:
                break;
            case BNAAL:
                break;
            case BNAN:
                break;
            case BNAZ:
                break;
            case BNAZAL:
                break;
            case BNE:
                break;
            case BNEAL:
                break;
            case BNEZ:
                break;
            case BNEZAL:
                break;
            case BRAP:
                break;
            case BRAPZ:
                break;
            case BRDNS:
                break;
            case BRDSE:
                break;
            case BREQ:
                break;
            case BREQZ:
                break;
            case BRGE:
                break;
            case BRGEZ:
                break;
            case BRGT:
                break;
            case BRGTZ:
                break;
            case BRLE:
                break;
            case BRLEZ:
                break;
            case BRLT:
                break;
            case BRLTZ:
                break;
            case BRNA:
                break;
            case BRNAN:
                break;
            case BRNAZ:
                break;
            case BRNE:
                break;
            case BRNEZ:
                break;
            case CEIL:
                break;
            case COS:
                break;
            case DIV:
                break;
            case EXP:
                break;
            case FLOOR:
                break;
            case J:
                break;
            case JAL:
                break;
            case JR:
                break;
            case L:
                break;
            case LB:
                break;
            case LBN:
                break;
            case LBNS:
                break;
            case LBS:
                break;
            case LOG:
                break;
            case LR:
                break;
            case LS:
                break;
            case MAX:
                break;
            case MIN:
                break;
            case MOD:
                break;
            case MOVE:
                break;
            case MUL:
                break;
            case NOR:
                break;
            case NOT:
                break;
            case OR:
                break;
            case PEEK:
                break;
            case POP:
                break;
            case PUSH:
                break;
            case RAND:
                break;
            case ROUND:
                break;
            case S:
                break;
            case SAP:
                break;
            case SAPZ:
                break;
            case SB:
                break;
            case SBN:
                break;
            case SBS:
                break;
            case SDNS:
                break;
            case SDSE:
                break;
            case SELECT:
                break;
            case SEQ:
                break;
            case SEQZ:
                break;
            case SGE:
                break;
            case SGEZ:
                break;
            case SGT:
                break;
            case SGTZ:
                break;
            case SIN:
                break;
            case SLA:
                break;
            case SLE:
                break;
            case SLEEP:
                break;
            case SLEZ:
                break;
            case SLL:
                break;
            case SLT:
                break;
            case SLTZ:
                break;
            case SNA:
                break;
            case SNAN:
                break;
            case SNANZ:
                break;
            case SNAZ:
                break;
            case SNE:
                break;
            case SNEZ:
                break;
            case SQRT:
                break;
            case SRA:
                break;
            case SRL:
                break;
            case SS:
                break;
            case SUB:
                break;
            case TAN:
                break;
            case TRUNC:
                break;
            case XOR:
                break;
            case CNULL:
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
