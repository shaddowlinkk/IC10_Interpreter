//
// Created by natha on 6/25/2023.
//

#include "../include/Lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TokenNode *NewToken(Token *token){
    TokenNode *newToken;
    newToken = (TokenNode *) malloc(sizeof(TokenNode));
    newToken->token= token;
    newToken->next= NULL;
}
void AddToken (TokenNode **head, TokenNode *newToken){
    TokenNode **tracker = head;
    while((*tracker)){
        tracker = &(*tracker)->next;
    }
    (*tracker)=newToken;

}
Token *stringlookup(char *curstring){
    int len = sizeof(commandList)/ sizeof(struct commandToken);
    Token *new = malloc(sizeof(Token));
    for(int i=0;i<len;i++){
        if(strcmp(curstring,commandList[i].str)==0){
             new->string=commandList[i].str;
             new->tokenType=commandList[i].tokentype;
             new->OP_type=commandList[i].OP_type;
             new->command=commandList[i].command;
            return new;
        }
    }
    return NULL;
}
void skipComments(char *data,int *pos){
    while (data[*pos]!='\n' && data[*pos]!='\0') {
        *pos=(*pos)+1;
    }
}

char *GetNextString(char *data,int *pos) {
    char *temp= malloc(100);
    memset(temp,'\0',100);

    while (data[*pos]!=' '&& data[*pos]!='\n' && data[*pos]!='\0') {
        if(data[*pos]=='#') {
            skipComments(data, pos);
            continue;
        }
        strncat(temp,&data[*pos],1);
        *pos=(*pos)+1;
        if(strcmp(temp,"HASH")==0){
            while (data[*pos]!= ')'){
                strncat(temp,&data[*pos],1);
                *pos=(*pos)+1;
            }

        }
    }
    return temp;
}

TokenNode *Lex(char *fileData){
    TokenNode *list= NULL;
    int pos=0;
    char *curString=NULL;
    while (fileData[pos]!='\0'){
        if(fileData[pos]=='#')
            skipComments(fileData,&pos);
        curString=GetNextString(fileData,&pos);
        Token *new = stringlookup(curString);
        if(new!=NULL) {
            AddToken(&list, NewToken(new));
            memset(curString,'\0',((sizeof(char))*100));

        }else if((int)*curString>=0x30&&(int)*curString<=0x39||(*curString=='-'&&(int)*(curString+1)>=0x30&&(int)*(curString+1)<=0x39)){
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *new2 = malloc(sizeof(Token));
            new2->tokenType=TT_NUM;
            new2->string=lit;
            new2->OP_type=TNULL;
            new2->command=CNULL;
            AddToken(&list, NewToken(new2));
            memset(curString,'\0',((sizeof(char))*100));
        }else if (strncmp(curString,"HASH",4)==0) {
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_HASH;
            nl->string=lit;
            nl->OP_type=TNULL;
            nl->command=CNULL;
            AddToken(&list, NewToken(nl));
            memset(curString,'\0',((sizeof(char))*100));
        }else if (strncmp(curString,"%",1)==0) {
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_NUM;
            nl->string=lit;
            nl->OP_type=TNULL;
            nl->command=CNULL;
            AddToken(&list, NewToken(nl));
            memset(curString,'\0',((sizeof(char))*100));
        }else if (strncmp(curString,"$",1)==0) {
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_NUM;
            nl->string=lit;
            nl->OP_type=TNULL;
            nl->command=CNULL;
            AddToken(&list, NewToken(nl));
            memset(curString,'\0',((sizeof(char))*100));
        }else if (strncmp((curString+(strlen(curString)-2)),":",1)==0 && strncmp(curString,"d",1)==0) {//< need to add for labels
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_DEVICE_CON;
            nl->string=lit;
            nl->OP_type=TNULL;
            AddToken(&list, NewToken(nl));
            memset(curString,'\0',((sizeof(char))*100));
        }else if (strncmp((curString+(strlen(curString)-1)),":",1)==0) {//< need to add for labels
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_LABEL;
            nl->string=lit;
            nl->OP_type=LABEL;
            nl->command=CNULL;
            AddToken(&list, NewToken(nl));
            memset(curString,'\0',((sizeof(char))*100));
        }else{
            if(strlen(curString)>0) {
                char *lit = malloc(strlen(curString) + 1);
                strncpy(lit,curString, strlen(curString) + 1);
                Token *nl = malloc(sizeof(Token));
                nl->tokenType = TT_STRING;
                nl->string = lit;
                nl->OP_type = TNULL;
                nl->command=CNULL;
                AddToken(&list, NewToken(nl));
                memset(curString, '\0', ((sizeof(char)) * 100));
            }
        }
        if(fileData[pos]=='\n'){
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_NEWLINE;
            nl->string="\\n";
            nl->OP_type=TNULL;
            nl->command=CNULL;
            AddToken(&list, NewToken(nl));
        }
        pos++;
    }
    return list;
}
void printlex(TokenNode *list){
    TokenNode **tracker = &list;
    int line=1;
    printf("line%d:  ", line);
    while (*tracker){

        printf("[string:%s,TT:%d,OP:%d]" ,(*tracker)->token->string,(*tracker)->token->tokenType,(*tracker)->token->OP_type);
        if((*tracker)->token->tokenType==TT_NEWLINE) {
            line++;
            printf("\nline%d:  ", line);
        }
        tracker = &(*tracker)->next;
    }
    printf("\n");
}
TokenNode *Lexer(char *Filename){
    FILE *file;
    file=fopen(Filename,"r");
    char *buffer=NULL;
    if(file){
        fseek(file,0,SEEK_END);
        int len = ftell(file);
        fseek(file,0,SEEK_SET);
        buffer= malloc(len+2);
        memset(buffer,'\0',len+2);
        if(buffer){
            fread(buffer,1,len,file);
        }
        fclose(file);
    }
    strcat(buffer,"\0");
    TokenNode *list = Lex(buffer);
    free(buffer);
    return list;
}