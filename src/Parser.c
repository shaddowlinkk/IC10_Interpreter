//
// Created by natha on 6/30/2023.
//

#include "../include/Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void addRedefine(struct parsedata *out,char *key,char *data){
    Key *new_key= malloc(sizeof(Key));
    int len =(int)strlen(key);
    new_key->size=len;
    new_key->size=(new_key->size<32)?new_key->size: 32;
    new_key->key= malloc(32);
    memset(new_key->key,0,32);
    strncpy_s(new_key->key,32,key,new_key->size);
    new_key->next=NULL;
    new_key->item=data;
    int index= keyhashcode(*new_key) % REDEF_SIZE;
    if(out->redef[index]==NULL){
        out->redef[index]=new_key;
    }else{
        Key  **trace;
        trace=&out->redef[index];
        while((*trace)->next){
            if((*trace)->next==NULL){
                (*trace)->next=new_key;
                break;
            } else{
                trace=&(*trace)->next;
            }
        }
    }
}
struct parsedata *Parse(TokenNode **tokenlist){
    struct parsedata *out = malloc(sizeof(struct parsedata));
    Statement *start = malloc(sizeof(Statement));
    start->stm_expr = NULL;
    start->statement = NULL;
    start->line=1;
    start->back=NULL;
    Statement **parsTracer = &start;
    TokenNode  **listtracer =tokenlist;
    memset(out->lables,0,sizeof(out->lables));
    memset(out->redef,0,sizeof(out->redef));
    out->lines=1;
    out->stmt=start;
    out->trace=NULL;
        while ((*listtracer)){
            if((*listtracer)->token->tokenType==TT_NEWLINE&&(*listtracer)->next!=NULL){
                out->lines++;
                if((*parsTracer)->stm_expr) {
                    Statement *new_state = malloc(sizeof(Statement));
                    new_state->stm_expr = NULL;
                    new_state->statement = NULL;
                    new_state->line=-1;
                    new_state->back=(*parsTracer);
                    (*parsTracer)->statement = new_state;
                    parsTracer = &(*parsTracer)->statement;
                    listtracer = &(*listtracer)->next;
                    continue;
                }
            }

            switch ((*listtracer)->token->OP_type) {
                case CMD:{
                    struct cmd *new = malloc(sizeof (struct cmd));
                    new->cop=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->cin1=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=CMD;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct cmd));
                    (* parsTracer)->stm_expr->expr->cmd=new;
                    (* parsTracer)->line=out->lines;
                    break;
                }
                case UNOP:{
                    struct unop *new = malloc(sizeof (struct unop));
                    new->uop=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->uout=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->uin1=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=UNOP;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct unop));
                    (* parsTracer)->stm_expr->expr->unop=new;
                    (* parsTracer)->line=out->lines;
                    if(new->uop->tokenType==TT_DEFINE || new->uop->tokenType==TT_ALIAS) {
                        if(new->uin1->tokenType!=TT_REG && new->uin1->tokenType!=TT_DEVICE&& new->uin1->tokenType!=TT_NUM)
                            break;
                        addRedefine(out, new->uout->string, new->uin1->string);
                    }
                    break;
                }
                case BINOP:{
                    struct binop *new = malloc(sizeof (struct binop));
                    new->bop=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->bout=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->bin1=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->bin2=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=BINOP;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct binop));
                    (* parsTracer)->stm_expr->expr->binop=new;
                    (* parsTracer)->line=out->lines;
                    break;
                }
                case TRIOP:{
                    struct triop *new = malloc(sizeof (struct triop));
                    new->top=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->tout=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->tin1=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->tin2=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->tin3=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=TRIOP;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct triop));
                    (* parsTracer)->stm_expr->expr->triop=new;
                    (* parsTracer)->line=out->lines;
                    break;
                }
                case QUADOP:{
                    struct quadop *new = malloc(sizeof (struct quadop));
                    new->qop=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->qout=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->qin1=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->qin2=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->qin3=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->qin4=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=QUADOP;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct quadop));
                    (* parsTracer)->stm_expr->expr->quadop=new;
                    (* parsTracer)->line=out->lines;
                    break;
                }
                case QUINOP:{
                    struct quinop *new = malloc(sizeof (struct quinop));
                    new->quop=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->quout=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->quin1=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->quin2=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->quin3=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->quin4=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->quin5=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=QUINOP;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct quinop));
                    (* parsTracer)->stm_expr->expr->quinop=new;
                    (* parsTracer)->line=out->lines;
                    break;
                }
                case SEXOP:{
                    struct sexop *new = malloc(sizeof (struct sexop));
                    new->sop=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sout=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sin1=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sin2=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sin3=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sin4=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sin5=(*listtracer)->token;
                    listtracer=&(*listtracer)->next;
                    new->sin6=(*listtracer)->token;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=SEXOP;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct sexop));
                    (* parsTracer)->stm_expr->expr->sexop=new;
                    (* parsTracer)->line=out->lines;
                    break;
                }
                case LABEL:{
                    struct cmd *new = malloc(sizeof (struct cmd));
                    new->cop=(*listtracer)->token;
                    new->cin1=NULL;
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=LABEL;
                    (* parsTracer)->stm_expr->expr= malloc(sizeof(struct cmd));
                    (* parsTracer)->stm_expr->expr->cmd=new;
                    Statement *new_state = malloc(sizeof(Statement));
                    (*parsTracer)->statement = new_state;
                    (* parsTracer)->line=out->lines;
                    out->lines++;
                    new_state->line=0;
                    new_state->stm_expr=NULL;
                    new_state->statement=NULL;
                    new_state->back=(*parsTracer);
                    Key *new_key= malloc(sizeof(Key));
                    int len =(int)strlen((*listtracer)->token->string);
                    new_key->size=len-1;
                    new_key->size=(new_key->size<32)?new_key->size: 32;
                    new_key->key= malloc(32);
                    memset(new_key->key,0,32);
                    strncpy_s(new_key->key,32,(*listtracer)->token->string,new_key->size);
                    new_key->next=NULL;
                    new_key->item=(*parsTracer);
                    int index= keyhashcode(*new_key) % 512;
                    if(out->lables[index]==NULL){
                        out->lables[index]=new_key;
                    }else{
                        Key  **trace;
                        trace=&out->lables[index];
                        while((*trace)->next){
                            if((*trace)->next==NULL){
                                (*trace)->next=new_key;
                                break;
                            } else{
                                trace=&(*trace)->next;
                            }
                        }
                    }
                    parsTracer = &(*parsTracer)->statement;
                    if((*listtracer)->next!=NULL){
                        listtracer=&(*listtracer)->next;
                    }
                    break;
                }
                case TNULL:
                    break;
                default:{
                    break;
                }
            }
            listtracer=&(*listtracer)->next;
        }
        out->lines=out->lines;
    Statement **tracer =&out->stmt;
    out->line_table= malloc(sizeof(Statement)* out->lines);
    memset(out->line_table,0, (sizeof(Statement)* out->lines));
    while (*tracer){
        out->line_table[(*tracer)->line-1]=(**tracer);
        tracer=&(*tracer)->statement;
    }
    addRedefine(out,"sp","r16");
    addRedefine(out,"ra","r17");
    return out;
}
void printTree(struct parsedata *tree){
    Statement **tracer = &tree->stmt;
    int line=0;
    printf("number of lines:%d\n",tree->lines);
    while (*tracer){
        line++;
        if((*tracer)->stm_expr) {
            printf("line:%d ",(*tracer)->line);
            switch ((*tracer)->stm_expr->type) {
                case UNOP:
                    printf("unop// cmd:%s ,out:%s,in:%s\n",
                           (*tracer)->stm_expr->expr->unop->uop->string,
                           (*tracer)->stm_expr->expr->unop->uout->string,
                           (*tracer)->stm_expr->expr->unop->uin1->string);
                    break;
                case BINOP:
                    printf("binop// cmd:%s ,out:%s,in:%s,in:%s\n",
                           (*tracer)->stm_expr->expr->binop->bop->string,
                           (*tracer)->stm_expr->expr->binop->bout->string,
                           (*tracer)->stm_expr->expr->binop->bin1->string,
                           (*tracer)->stm_expr->expr->binop->bin2->string);
                    break;
                case TRIOP:
                    printf("triop// cmd:%s ,out:%s,in:%s,in:%s,in:%s\n",
                           (*tracer)->stm_expr->expr->triop->top->string,
                           (*tracer)->stm_expr->expr->triop->tout->string,
                           (*tracer)->stm_expr->expr->triop->tin1->string,
                           (*tracer)->stm_expr->expr->triop->tin2->string,
                           (*tracer)->stm_expr->expr->triop->tin3->string);
                    break;
                case QUADOP:
                    printf("quadop// cmd:%s ,out:%s,in:%s,in:%s,in:%s,in:%s\n",
                           (*tracer)->stm_expr->expr->quinop->quop->string,
                           (*tracer)->stm_expr->expr->quadop->qout->string,
                           (*tracer)->stm_expr->expr->quadop->qin1->string,
                           (*tracer)->stm_expr->expr->quadop->qin2->string,
                           (*tracer)->stm_expr->expr->quadop->qin3->string,
                           (*tracer)->stm_expr->expr->quadop->qin4->string);
                    break;
                case QUINOP:
                    printf("quinop// cmd:%s ,out:%s,in:%s,in:%s,in:%s,in:%s,in:%s\n",
                           (*tracer)->stm_expr->expr->quinop->quop->string,
                           (*tracer)->stm_expr->expr->quinop->quout->string,
                           (*tracer)->stm_expr->expr->quinop->quin1->string,
                           (*tracer)->stm_expr->expr->quinop->quin2->string,
                           (*tracer)->stm_expr->expr->quinop->quin3->string,
                           (*tracer)->stm_expr->expr->quinop->quin4->string,
                           (*tracer)->stm_expr->expr->quinop->quin5->string);
                    break;
                case SEXOP:
                    printf("sexop// cmd:%s ,out:%s,in:%s,in:%s,in:%s,in:%s,in:%s,in:%s\n",
                           (*tracer)->stm_expr->expr->sexop->sop->string,
                           (*tracer)->stm_expr->expr->sexop->sout->string,
                           (*tracer)->stm_expr->expr->sexop->sin1->string,
                           (*tracer)->stm_expr->expr->sexop->sin2->string,
                           (*tracer)->stm_expr->expr->sexop->sin3->string,
                           (*tracer)->stm_expr->expr->sexop->sin4->string,
                           (*tracer)->stm_expr->expr->sexop->sin5->string,
                           (*tracer)->stm_expr->expr->sexop->sin6->string);
                    break;
                case CMD:
                    printf("cmd// cmd:%s ,in:%s\n",
                           (*tracer)->stm_expr->expr->cmd->cop->string,
                           (*tracer)->stm_expr->expr->cmd->cin1->string);
                    break;
                case LABEL:
                    printf("label//\n");
                    break;
                case TNULL:
                    printf("this is fucked l:%d\n", line);
                    break;
            }
        }
        tracer=&(*tracer)->statement;
    }
}
