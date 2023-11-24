//
// Created by nathan_pc on 10/15/2023.
//

#include "../include/executor.h"
#include "../include/parser.h"
#include "../include/readEnviroment.h"
#include "../include/interp_math.h"
#include <ctype.h>
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

double getRegisterData(const char *token,Enviro *env,struct parsedata *pdata){
    //can be optimized useing pointer arithmatic
    double data;
    int len = (int)strlen(token);
    if(token[0]=='r'&&token[1]=='r'){
        char *tmp = malloc(len-1);
        strncpy(tmp,&token[1],len-1);
        data=env->regs[(int)floor(getRegisterData(tmp,env,pdata))];
        return data;
    }else if((token[1]>='0'&&token[1]<='9')){
        int idx= strtol(&token[1],NULL,0);
        data=env->regs[idx];
        return data;
    }else{
        return strtol(&token[0],NULL,0);
    }
}
double getDataForInToken(Token *token,Enviro *env,struct parsedata *pdata){
    int index=(hashcode(strlen(token->string),token->string)%REDEF_SIZE);
    if (token->tokenType==TT_NUM||token->tokenType==TT_REG){
        return (token->tokenType==TT_NUM)? strtod(token->string,NULL): getRegisterData(token->string,env,pdata);
    }else if(pdata->redef[index]!=NULL){
        char *p=pdata->redef[index]->item;
        return (*p=='r')? getRegisterData(p,env,pdata): strtod(p,NULL);
    }
    return 0;
}
int getOutReg(Token *token,Enviro *env,struct parsedata *pdata){
    double out;
    int index=(hashcode(strlen(token->string),token->string)%REDEF_SIZE);
    if (token->tokenType==TT_REG){
        return floor(getRegisterData(token->string+1,env,pdata));
    }else if(pdata->redef[index]!=NULL){
        char *p=pdata->redef[index]->item;
        if(*p=='r'){
            return floor(getRegisterData((p+1),env,pdata));
        } else{
            exit(-5);
        }
    }
    return 0;
}
int getDeviceNum(Enviro *env, struct parsedata *pdata,Token *token){
    int index=(hashcode(strlen(token->string),token->string)%REDEF_SIZE);
    if (token->tokenType==TT_DEVICE){
        return floor(getRegisterData(token->string+1,env,pdata));
    }
    else if(pdata->redef[index]!=NULL){
        char *p=pdata->redef[index]->item;
        if(*p=='d'){
            return floor(getRegisterData((p+1),env,pdata));
        } else{
            exit(-7);
        }
    }
}
void execute_unary_math(struct unop *data, Enviro *env, struct parsedata *pdata, double (*opt) (double )){
        int idx=getOutReg(data->uout,env,pdata);
        double fin=getDataForInToken(data->uin1,env,pdata);
        env->regs[idx]= (*opt)(fin);

}
void execute_binary_math(struct binop *data, Enviro *env, struct parsedata *pdata, double (*opt) (double,double )){
    int idx = getOutReg(data->bout, env, pdata);
    double fin1 = getDataForInToken(data->bin1, env, pdata);
    double fin2 = getDataForInToken(data->bin2, env, pdata);
    env->regs[idx]= (*opt)(fin1,fin2);

}
void jumpToLineNumber(Enviro *env,struct parsedata *pdata,int num){
    int idx=num-1;// need to be this so the incremnet will index the jump right other option is to execute now so
    while ((pdata->line_table+(sizeof (Statement)*idx))==NULL&& idx<pdata->lines){
        idx++;
    }
    if(idx>=pdata->lines){
        *pdata->trace=NULL;
    }else if(pdata->line_table[idx].back!=NULL) {
        pdata->trace = &pdata->line_table[idx].back->statement;
    }else{
        pdata->trace=&pdata->stmt;
    }
}
void execute_jump(Enviro *env,struct parsedata *pdata,Token *jumploc){
    //todo be able jump to aliased location or jump using registers
    int index=(hashcode(strlen(jumploc->string),jumploc->string)%512);
    if(jumploc->tokenType==TT_NUM){
        int idx= (int)floor(strtod(jumploc->string,NULL));
        jumpToLineNumber(env,pdata,idx);
    }else if (pdata->lables[index]!=NULL){
        if(((Statement *) (pdata->lables[index]->item))->back!=NULL) {
            pdata->trace = &((Statement *) (pdata->lables[index]->item))->back->statement;
        }else{
            pdata->trace=&pdata->stmt;
        }
    }else{
        exit(-6);
    }
}
enum jumpType{N,AL,R};
void jump(Enviro *env,struct parsedata *pdata,Token *jumploc,enum jumpType type){
    switch (type) {
        case N: {
            execute_jump(env, pdata, jumploc);
            break;
        }
        case AL: {
            env->regs[17]=(*pdata->trace)->line+1;
            execute_jump(env, pdata, jumploc);
            break;
        }
        case R: {
            int ofset=(int)floor((getDataForInToken(jumploc,env,pdata)));
            int loc=(*pdata->trace)->line+ofset;
            jumpToLineNumber(env,pdata,loc);
            break;
        }
    }

}
int approx(double a,double b,double c){
    if(fabs(a-b)<=max((c*max(a,b)),1.1210387714598537E-44))
        return 1;
    return 0;
}
int checkForDeviceConnected(Enviro *env,int devNum){
    Device **start=env->devices;
    for (Device **end = &env->devices[env->numdevs]; start <=end ; start++) {
        if((*start)->device_num==devNum){
            return 1;
        }
    }
    return 0;
}
int getHashValue(Token *token){
    unsigned long long len= strlen(token->string);
    char *p= token->string;
    int flag=0;
    int size=-1;
    for (void *stop=&p[len];p!=stop;p++){
        flag=(*p=='"')? ((flag+1)%2):flag;
        if(flag){
            size++;
        }
    }
    char *tmp= malloc(size+1);
    memset(tmp,0,size+1);
    strncpy(tmp,token->string+6,size);
    int out = crc32b(tmp);
    free(tmp);
    return out;
}
void execute_load(Enviro *env,struct parsedata *pdata,struct binop *exper){
    int outreg= getOutReg(exper->bout,env,pdata);
    int dev= getDeviceNum(env,pdata,exper->bin1);
    Device **start=env->devices;
    for (Device **end = &env->devices[env->numdevs]; start <=end ; start++) {
        if((*start)->device_num==dev){
            tolowerall(exper->bin2->string,strlen(exper->bin2->string));
            int idx=(hashcode(strlen(exper->bin2->string), exper->bin2->string) % STORAGE_SIZE);
            if((*start)->deviceParams[idx]!=NULL) {
                env->regs[outreg] = (*((double *) (*start)->deviceParams[idx]->item));
            }else{
                char err[100];
                sprintf(err,"could not find device Param enters line number:%d\n",(*pdata->trace)->line);
                perror(err);
            }
        }
    }
}
/**
 * this function is used to execute one statement on provided environment
 * @param trace the pointer to a pointer that is the statement that you want to execute
 * @param env the environment that you want to execute agents
 * @param pdata the parsed data which includes labels and redefinitions
 */
void execute_stmt(Enviro *env,struct parsedata *pdata){
    Statement **trace=pdata->trace;
    if((*trace)->stm_expr->type!=LABEL) {
        switch (getTokenType((*trace)->stm_expr)) {
            case ABS:{
                execute_unary_math((*trace)->stm_expr->expr->unop, env, pdata, fabs);
                break;
            }
            case ACOS:{
                execute_unary_math((*trace)->stm_expr->expr->unop, env, pdata, acos);
                break;
            }
            case ADD: {
                execute_binary_math((*trace)->stm_expr->expr->binop, env, pdata, CADD);
                break;
            }
            case AND: {
                execute_binary_math((*trace)->stm_expr->expr->binop, env, pdata, CAND);
                break;
            }
            case ASIN:{
                execute_unary_math((*trace)->stm_expr->expr->unop, env, pdata, asin);
                break;
            }
            case ATAN:
                execute_unary_math((*trace)->stm_expr->expr->unop, env, pdata, atan);
                break;
            case ATAN2: {
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,atan2);
                break;
            }
            case BAP: {
                double a= getDataForInToken((*trace)->stm_expr->expr->triop->tout,env,pdata);
                double b= getDataForInToken((*trace)->stm_expr->expr->triop->tin1,env,pdata);
                double c= getDataForInToken((*trace)->stm_expr->expr->triop->tin2,env,pdata);
                if(approx(a,b,c)){
                    jump(env,pdata,(*trace)->stm_expr->expr->triop->tin3,N);
                    return;
                }
                break;
            }
            case BAPAL: {
                double a = getDataForInToken((*trace)->stm_expr->expr->triop->tout, env, pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->triop->tin1, env, pdata);
                double c = getDataForInToken((*trace)->stm_expr->expr->triop->tin2, env, pdata);
                if (approx(a, b, c)) {
                    jump(env, pdata, (*trace)->stm_expr->expr->triop->tin3,AL);
                    return;
                }
                break;
            }
            case BAPZ: {
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(approx(a,0,b)){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,N);
                    return;
                }
                break;
            }
            case BAPZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(approx(a,0,b)){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,AL);
                    return;
                }
                break;
            }
            case BDNS:{
                int dn= getDeviceNum(env,pdata,(*trace)->stm_expr->expr->unop->uout);
                if(!checkForDeviceConnected(env,dn)){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BDNSAL:{
                int dn= getDeviceNum(env,pdata,(*trace)->stm_expr->expr->unop->uout);
                if(!checkForDeviceConnected(env,dn)){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BDSE:{
                int dn= getDeviceNum(env,pdata,(*trace)->stm_expr->expr->unop->uout);
                if(checkForDeviceConnected(env,dn)){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BDSEAL:{
                int dn= getDeviceNum(env,pdata,(*trace)->stm_expr->expr->unop->uout);
                if(checkForDeviceConnected(env,dn)){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BEQ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a==b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,N);
                    return;
                }
                break;
            }
            case BEQAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a==b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,AL);
                    return;
                }
                break;
            }
            case BEQZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a==0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BEQZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a==0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BGE:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a>=b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,N);
                    return;
                }
                break;
            }
            case BGEAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a>=b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,AL);
                    return;
                }
                break;
            }
            case BGEZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a>=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BGEZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a>=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BGT:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a>b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,N);
                    return;
                }
                break;
            }
            case BGTAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a>b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,AL);
                    return;
                }
                break;
            }
            case BGTZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a>0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BGTZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a>0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BLE: {
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if (a<=b) {
                    jump(env, pdata, (*trace)->stm_expr->expr->binop->bin2, N);
                    return;
                }
                break;
            }
            case BLEAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if (a<=b) {
                    jump(env, pdata, (*trace)->stm_expr->expr->binop->bin2, AL);
                    return;
                }
                break;
            }
            case BLEZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a<=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BLEZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a<=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BLT: {
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if (a<b) {
                    jump(env, pdata, (*trace)->stm_expr->expr->binop->bin2, N);
                    return;
                }
                break;
            }
            case BLTAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if (a<b) {
                    jump(env, pdata, (*trace)->stm_expr->expr->binop->bin2, AL);
                    return;
                }
                break;
            }
            case BLTZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a<0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BLTZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a<0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BNA:
                //not defined well in game will have to look at source
                break;
            case BNAAL:
                //not defined well in game will have to look at source
                break;
            case BNAN:
                // dont know how reping not num rightnow
                break;
            case BNAZ:
                //not defined well in game will have to look at source
                break;
            case BNAZAL:
                //not defined well in game will have to look at source
                break;
            case BNE:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if (a!=b) {
                    jump(env, pdata, (*trace)->stm_expr->expr->binop->bin2, N);
                    return;
                }
                break;
            }
            case BNEAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if (a!=b) {
                    jump(env, pdata, (*trace)->stm_expr->expr->binop->bin2, AL);
                    return;
                }
                break;
            }
            case BNEZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a!=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,N);
                    return;
                }
                break;
            }
            case BNEZAL:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a!=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,AL);
                    return;
                }
                break;
            }
            case BRAP:
                //not defined well in game will have to look at source
                break;
            case BRAPZ:
                //not defined well in game will have to look at source
                break;
            case BRDNS:{
                int dn= getDeviceNum(env,pdata,(*trace)->stm_expr->expr->unop->uout);
                if(!checkForDeviceConnected(env,dn)){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BRDSE:{
                int dn= getDeviceNum(env,pdata,(*trace)->stm_expr->expr->unop->uout);
                if(checkForDeviceConnected(env,dn)){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BREQ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a==b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,R);
                    return;
                }
                break;
            }
            case BREQZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a==0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BRGE:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a>=b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,R);
                    return;
                }
                break;
            }
            case BRGEZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a>=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BRGT:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a>b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,R);
                    return;
                }
                break;
            }
            case BRGTZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a>0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BRLE:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a<=b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,R);
                    return;
                }
                break;
            }
            case BRLEZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a<=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BRLT:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a<b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,R);
                    return;
                }
                break;
            }
            case BRLTZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a<0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case BRNA:
                //not defined well in game will have to look at source
                break;
            case BRNAN:
                // dont know how reping not num rightnow
                break;
            case BRNAZ:
                //not defined well in game will have to look at source
                break;
            case BRNE:{
                double a = getDataForInToken((*trace)->stm_expr->expr->binop->bout,env,pdata);
                double b = getDataForInToken((*trace)->stm_expr->expr->binop->bin1,env,pdata);
                if(a!=b){
                    jump(env,pdata,(*trace)->stm_expr->expr->binop->bin2,R);
                    return;
                }
                break;
            }
            case BRNEZ:{
                double a = getDataForInToken((*trace)->stm_expr->expr->unop->uout,env,pdata);
                if(a!=0){
                    jump(env,pdata,(*trace)->stm_expr->expr->unop->uin1,R);
                    return;
                }
                break;
            }
            case CEIL:
                execute_unary_math((*trace)->stm_expr->expr->unop,env,pdata,ceil);
                break;
            case COS:
                execute_unary_math((*trace)->stm_expr->expr->unop,env,pdata,cos);
                break;
            case DIV:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,CDIV);
                break;
            case EXP:
                execute_unary_math((*trace)->stm_expr->expr->unop,env,pdata,exp);
                break;
            case FLOOR:
                execute_unary_math((*trace)->stm_expr->expr->unop,env,pdata,floor);
                break;
            case J: {
                jump(env,pdata,(*trace)->stm_expr->expr->cmd->cin1,N);
                return;
            }
            case JAL: {
                jump(env, pdata, (*trace)->stm_expr->expr->cmd->cin1,AL);
                return;
            }
            case JR:{

                jump(env,pdata,(*trace)->stm_expr->expr->cmd->cin1,R);
                return;
            }
            case L: {
                execute_load(env,pdata,(*trace)->stm_expr->expr->binop);
                break;
            }
            case LB: {
                getHashValue((*trace)->stm_expr->expr->triop->tin1);
                break;
            }
            case LBN:
                break;
            case LBNS:
                break;
            case LBS:
                break;
            case LOG:
                execute_unary_math((*trace)->stm_expr->expr->unop,env,pdata,log);
                break;
            case LR:
                break;
            case LS:
                break;
            case MAX:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,max);
                break;
            case MIN:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,min);
                break;
            case MOD:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,fmod);
                break;
            case MOVE:{
                if((*trace)->stm_expr->expr->unop->uout->tokenType==TT_REG){
                    int idx= getOutReg((*trace)->stm_expr->expr->unop->uout,env,pdata);
                    double fin= getDataForInToken((*trace)->stm_expr->expr->unop->uin1,env,pdata);
                    env->regs[idx]=fin;
                }
                break;
            }
            case MUL:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,CMUL);
                break;
            case NOR:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,CNOR);
                break;
            case NOT:
                execute_unary_math((*trace)->stm_expr->expr->unop,env,pdata,CNOT);
                break;
            case OR:
                execute_binary_math((*trace)->stm_expr->expr->binop,env,pdata,COR);
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
    pdata->trace = &(*pdata->trace)->statement;
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
