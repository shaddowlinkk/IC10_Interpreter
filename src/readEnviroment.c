//
// Created by nathan_pc on 10/15/2023.
//

#include "../include/readEnviroment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
char *GetNextEniroString(char *data,int *pos) {
    char *temp= malloc(100);
    memset(temp,'\0',100);

    while (data[*pos]!='\n' && data[*pos]!='\0') {
        if(data[*pos]<=90 &&data[*pos]>=65){
            data[*pos]=data[*pos]+32;
        }
        strncat_s(temp,100,&data[*pos],1);
        *pos=(*pos)+1;
    }
    return temp;
}
Device **getDevices(char *data,int *pos){
    char *temp= malloc(100);
    int devices=0;
    while (!(data[*pos]=='}' && data[((*pos)+1)]!=',')) {
        if((data[*pos]=='}' && data[((*pos)+1)]==',')) {
            printf("\tnext\n");
            devices++;
            *pos=(*pos)+2;
        }
        if (data[*pos] != '\t' && data[*pos] != '{' && data[*pos] != '\n') {
            char *temp = GetNextEniroString(data, pos);
            if(temp[0]=='[') {
                printf("\tdevice control:%s\n", temp);
            }else{
                printf("\tdevice data:%s\n", temp);
            }
        }
        *pos=(*pos)+1;
    }
    printf("end\n");
    *pos=(*pos)+1;
}
Enviro *proccesFile(char *fileData,int size){
    Enviro *out = malloc(sizeof(Enviro));
    int pos=0;
    while (fileData[pos]!='\0') {
        if (fileData[pos]!='\t') {
            char *temp = GetNextEniroString(fileData, &pos);
            if(temp[0]=='['){
               if(strncmp(temp,"[devices",8)==0) {
                   printf("control:%s\n", temp);
                   getDevices(fileData, &pos);
               }else if(strncmp(temp,"[registers",10)==0){
                   printf("control:%s\n", temp);
               }else if(strncmp(temp,"[stack",6)==0){
                   printf("control:%s\n", temp);
               }else{
                   printf("string:%s\n", temp);
               }
            }else{
                printf("data:%s\n", temp);
            }
        }
        pos++;
    }
    return out;
}
Enviro *readinEniro(char *Filename){
    FILE *file;
    file=fopen(Filename,"r");
    char *buffer=NULL;
    int len;
    if(file){
        fseek(file,0,SEEK_END);
        len = ftell(file);
        fseek(file,0,SEEK_SET);
        buffer= malloc(len+2);
        memset(buffer,'\0',len+2);
        if(buffer){
            fread(buffer,1,len,file);
        }
        fclose(file);
    }
    strcat(buffer,"\0");
    Enviro *out= proccesFile(buffer,(len+1));
    return out;
}