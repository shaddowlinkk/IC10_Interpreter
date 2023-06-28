//
// Created by natha on 6/25/2023.
//

#include "Lexer.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct commandToken commandList[]={
        {"abs",TT_MATH},
        {"acos",TT_MATH},
        {"add",TT_BINOP},
        {"alias",TT_ALIAS},
        {"and",TT_BITOP},
        {"asin",TT_MATH},
        {"atan",TT_MATH},
        {"atan2",TT_MATH},
        {"bap",TT_JUMP},
        {"bapal",TT_JUMP},
        {"bapz",TT_JUMP},
        {"bapzal",TT_JUMP},
        {"bdns",TT_JUMP},
        {"bdnsal",TT_JUMP},
        {"bdse",TT_JUMP},
        {"bdseal",TT_JUMP},
        {"beq",TT_JUMP},
        {"beqal",TT_JUMP},
        {"beqz",TT_JUMP},
        {"beqzal",TT_JUMP},
        {"bge",TT_JUMP},
        {"bgeal",TT_JUMP},
        {"bgez",TT_JUMP},
        {"bgezal",TT_JUMP},
        {"bgt",TT_JUMP},
        {"bgtal",TT_JUMP},
        {"bgtz",TT_JUMP},
        {"bgtzal",TT_JUMP},
        {"ble",TT_JUMP},
        {"bleal",TT_JUMP},
        {"blez",TT_JUMP},
        {"blezal",TT_JUMP},
        {"blt",TT_JUMP},
        {"bltal",TT_JUMP},
        {"bltz",TT_JUMP},
        {"bltzal",TT_JUMP},
        {"bna",TT_JUMP},
        {"bnaal",TT_JUMP},
        {"bnan",TT_JUMP},
        {"bnaz",TT_JUMP},
        {"bnazal",TT_JUMP},
        {"bne",TT_JUMP},
        {"bneal",TT_JUMP},
        {"bnez",TT_JUMP},
        {"bnezal",TT_JUMP},
        {"brap",TT_RJUMP},
        {"brapz",TT_RJUMP},
        {"brdns",TT_RJUMP},
        {"brdse",TT_RJUMP},
        {"breq",TT_RJUMP},
        {"breqz",TT_RJUMP},
        {"brge",TT_RJUMP},
        {"brgez",TT_RJUMP},
        {"brgt",TT_RJUMP},
        {"brgtz",TT_RJUMP},
        {"brle",TT_RJUMP},
        {"brlez",TT_RJUMP},
        {"brlt",TT_RJUMP},
        {"brltz",TT_RJUMP},
        {"brna",TT_RJUMP},
        {"brnan",TT_RJUMP},
        {"brnaz",TT_RJUMP},
        {"brne",TT_RJUMP},
        {"brnez",TT_RJUMP},
        {"ceil",TT_MATH},
        {"cos",TT_MATH},
        {"define",TT_DEFINE},
        {"div",TT_BINOP},
        {"exp",TT_MATH},
        {"floor",TT_MATH},
        {"hcf",TT_LOL},
        {"j",TT_JUMP},
        {"jal",TT_JUMP},
        {"jr",TT_RJUMP},
        {"l",TT_LOAD},
        {"lb",TT_LOAD},
        {"lbn",TT_LOAD},
        {"lbns",TT_LOAD},
        {"lbs",TT_LOAD},
        {"log",TT_MATH},
        {"lr",TT_LOAD},
        {"ls",TT_LOAD},
        {"max",TT_MATH},
        {"min",TT_MATH},
        {"mod",TT_MATH},
        {"move",TT_MOVE},
        {"mul",TT_BINOP},
        {"nor",TT_BITOP},
        {"or",TT_BITOP},
        {"peek",TT_STACK},
        {"pop",TT_STACK},
        {"push",TT_STACK},
        {"rand",TT_MATH},
        {"round",TT_MATH},
        {"s",TT_SET},
        {"sap",TT_SELECT},
        {"sapz",TT_SELECT},
        {"sb",TT_SET},
        {"sbn",TT_SET},
        {"sbs",TT_SET},
        {"sdns",TT_SELECT},
        {"sdse",TT_SELECT},
        {"select",TT_SELECT},
        {"seq",TT_SELECT},
        {"seqz",TT_SELECT},
        {"sge",TT_SELECT},
        {"sgez",TT_SELECT},
        {"sgt",TT_SELECT},
        {"sgtz",TT_SELECT},
        {"sin",TT_MATH},
        {"sla",TT_SHIFT},
        {"sle",TT_SELECT},
        {"sleep",TT_WAIT},
        {"slez",TT_SELECT},
        {"sll",TT_SHIFT},
        {"slt",TT_SELECT},
        {"sltz",TT_SELECT},
        {"sna",TT_SELECT},
        {"snan",TT_SELECT},
        {"snanz",TT_SELECT},
        {"snaz",TT_SELECT},
        {"sne",TT_SELECT},
        {"snez",TT_SELECT},
        {"sqrt",TT_MATH},
        {"sra",TT_SHIFT},
        {"srl",TT_SHIFT},
        {"ss",TT_SET},
        {"sub",TT_BINOP},
        {"tan",TT_MATH},
        {"trunc",TT_MATH},
        {"xor",TT_BITOP},
        {"yield",TT_WAIT},
        {"r0",TT_REG},
        {"r1",TT_REG},
        {"r2",TT_REG},
        {"r3",TT_REG},
        {"r4",TT_REG},
        {"r5",TT_REG},
        {"r6",TT_REG},
        {"r7",TT_REG},
        {"r8",TT_REG},
        {"r9",TT_REG},
        {"r10",TT_REG},
        {"r11",TT_REG},
        {"r12",TT_REG},
        {"r13",TT_REG},
        {"r14",TT_REG},
        {"r15",TT_REG},
        {"r16",TT_REG},
        {"r17",TT_REG}
};



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
            return new;
        }
    }
    return NULL;
}
void skipComments(char *data,int *pos){
    while (data[*pos]!=' '&& data[*pos]!='\n' && data[*pos]!='\0') {
        *pos=(*pos)+1;
    }
}
char *GetNextString(char *data,int *pos) {
    char *temp= malloc(100);
    memset(temp,'\0',100);
    if(data[*pos]=='#')
        skipComments(data,pos);
    while (data[*pos]!=' '&& data[*pos]!='\n' && data[*pos]!='\0') {
        strncat(temp,&data[*pos],1);
        *pos=(*pos)+1;
    }
    return temp;
}
TokenNode *Lex(char *fileData){
    TokenNode *list= NULL;
    int pos=0;
    char *curString=NULL;
    while (fileData[pos]!='\0'){
        curString=GetNextString(fileData,&pos);
        Token *new = stringlookup(curString);
        if(new!=NULL) {
            AddToken(&list, NewToken(new));
            memset(curString,'\0',((sizeof(char))*100));

        }else if((int)*curString>=0x30&&(int)*curString<=0x39||(*curString=='-'&&(int)*(curString-1)>=0x30&&(int)*(curString-1)<=0x39)){
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *new2 = malloc(sizeof(Token));
            new2->tokenType=TT_NUM;
            new2->string=lit;
            AddToken(&list, NewToken(new2));
            memset(curString,'\0',((sizeof(char))*100));
        }else{
            char *lit= malloc(strlen(curString)+1);
            strncpy(lit,curString, strlen(curString)+1);
            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_STRING;
            nl->string=lit;
            AddToken(&list, NewToken(nl));
            memset(curString,'\0',((sizeof(char))*100));
        }
        if(fileData[pos]=='\n'){

            Token *nl = malloc(sizeof(Token));
            nl->tokenType=TT_NEWLINE;
            nl->string="\\n";
            AddToken(&list, NewToken(nl));
        }
        pos++;
    }
    return list;
}
void printlex(TokenNode *list){
    TokenNode **tracker = &list;
    while (*tracker){
        printf("[string:%s,TT:%d]" ,(*tracker)->token->string,(*tracker)->token->tokenType);
        if((*tracker)->token->tokenType==TT_NEWLINE)
            printf("\n");
        tracker = &(*tracker)->next;
    }
}
TokenNode *Lexer(char *Filename){
    FILE *file;
    file=fopen("tst.txt","r");
    char *buffer=NULL;
    if(file){
        fseek(file,0,SEEK_END);
        int len = ftell(file);
        fseek(file,0,SEEK_SET);
        buffer= malloc(len);
        memset(buffer,'\0',len);
        if(buffer){
            fread(buffer,1,len,file);
        }
        fclose(file);
    }
    TokenNode *list = Lex(buffer);
    printlex(list);
    return list;
}