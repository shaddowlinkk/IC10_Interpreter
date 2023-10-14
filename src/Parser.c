//
// Created by natha on 6/30/2023.
//

#include "../Include/Parser.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct parsetree *Parse(TokenNode **tokenlist){
    struct parsetree *out = malloc(sizeof(struct parsetree));
    Statement *start = malloc(sizeof(Statement));
    start->stm_expr = NULL;
    start->statement = NULL;
    start->line=1;
    start->back=NULL;
    Statement **parsTracer = &start;
    TokenNode  **listtracer =tokenlist;
    memset(out->lables,-1,512);
    out->lines=1;
    out->stmt=start;
    int lab=0;
        while ((*listtracer)){
            if((*listtracer)->token->tokenType==TT_NEWLINE){
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
                    (* parsTracer)->stm_expr= malloc(sizeof(Exper));
                    (* parsTracer)->stm_expr->type=LABEL;
                    /*
                     * add to a map (* parsTracer)->statment to str
                     */
                    Statement *new_state = malloc(sizeof(Statement));
                    (*parsTracer)->statement = new_state;
                    (* parsTracer)->line=out->lines;
                    out->lines++;
                    new_state->line=0;
                    new_state->stm_expr=NULL;
                    new_state->statement=NULL;
                    new_state->back=(*parsTracer);
                    out->lables[lab]= (int) (*parsTracer)->statement;
                    parsTracer = &(*parsTracer)->statement;
                    listtracer=&(*listtracer)->next;
                    lab++;
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
    return out;
}
void printTree(struct parsetree *tree){
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
