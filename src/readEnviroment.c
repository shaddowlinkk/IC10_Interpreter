//
// Created by nathan_pc on 10/15/2023.
//

#include "../include/readEnviroment.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/Util.h"
#define STORAGE_SIZE 512

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
void splitqw(char *data,char **out){
    int pos=0;
    memset(out,0, sizeof(out));
    int index=0;
    char *temp= malloc(50);
    memset(temp,'\0',50);
    strcat(data,"\0");
    int size=0;
    while (data[pos]!='\0'){
        if (data[pos] != '\t' && data[pos] != '{'&& data[pos] != '"') {
            if (data[pos] == '=') {
                size++;
                out[index] = malloc(size);
                memset(out[index],0,size);
                strncpy_s(out[index], size, temp, size);
                memset(temp, '\0', 50);
                pos++;
                index++;
                continue;
            }
            strncat_s(temp, 50, &data[pos], 1);
            size++;
        }
        pos++;
    }
    size++;
    out[index]= malloc(size);
    memset(out[index],0,size);
    strncpy_s(out[index],size,temp,size);
    //printf("\t\tdata:\n\t\t\tparam_name:%s\n\t\t\tparam_name:%s\n",out[0],out[1]);
}
void addToDeviceStorage(char ** data, Key **storage){

    double con = strtod(data[1],NULL);
    Key *newKey= malloc(sizeof(newKey));
    newKey->size= strlen(data[0]);
    newKey->next=NULL;
    newKey->key= malloc(32);
    memset(newKey->key,0,32);
    strncpy_s(newKey->key,32,data[0],newKey->size);
    newKey->item=&con;
    int index=keyhashcode(*newKey)%STORAGE_SIZE;
    if(storage[index]==NULL){
        storage[index]=newKey;
    }else{
        Key  **trace;
        trace=&storage[index];
        while((*trace)->next){
            if((*trace)->next==NULL){
                (*trace)->next=newKey;
                break;
            } else{
                trace=&(*trace)->next;
            }
        }
    }
}
Device **getDevices(char *data,int *pos){
    Device device_list[10];
    int devices=0;
    Device *new_d = malloc(sizeof(Device));
    new_d->deviceParams=NULL;
    new_d->slotParams=NULL;
    new_d->deviceSettings=NULL;
    new_d->name=NULL;
    new_d->name_size=0;
    enum device_storage{settings,param,slot_param};
    int currstate=0;
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
                if(strncmp(temp,"[device settings]",17)==0){
                    currstate=settings;
                }
                if(strncmp(temp,"[device params]",15)==0){
                    currstate=param;
                }
                if(strncmp(temp,"[slot params]",13)==0){
                    currstate=slot_param;
                }else {
                }
            }else{
                char *out[2];
                splitqw(temp,out);
                if(strncmp(out[0],"name",4)==0){
                    int size = strlen(out[1]);
                    new_d->name_size=size;
                    size++;
                    new_d->name= malloc(size);
                    memset(new_d->name,0,size);
                    strncpy_s(new_d->name,size,out[1],size-1);
                    printf("\t\tname:\n\t\t\tparam_name:%s\n\t\t\tparam_val:%s\n",out[0],out[1]);
                }else {
                    switch (currstate) {
                        case settings: {
                            if(new_d->deviceSettings==NULL){
                                new_d->deviceSettings=malloc(sizeof(Key)*STORAGE_SIZE);
                                memset(new_d->deviceSettings,0,sizeof (Key)*STORAGE_SIZE);
                            }
                            addToDeviceStorage(out, new_d->deviceSettings);
                            int index=(hashcode(strlen(out[0]),out[0])%STORAGE_SIZE);
                            printf("\t\tname:\n\t\t\tparam_name:%s\n\t\t\tparam_val:%.1lf\n",new_d->deviceSettings[index]->key,(*((double *)new_d->deviceSettings[index]->item)));
                            break;
                        }
                        case param: {
                            if(new_d->deviceParams==NULL){
                                new_d->deviceParams=malloc(sizeof(Key)*STORAGE_SIZE);
                                memset(new_d->deviceParams,0,sizeof (Key)*STORAGE_SIZE);
                            }
                            addToDeviceStorage(out, new_d->deviceParams);
                            int index=(hashcode(strlen(out[0]),out[0])%STORAGE_SIZE);
                            printf("\t\tdevice param data:\n\t\t\tparam_name:%s\n\t\t\tparam_val:%.1lf\n",new_d->deviceParams[index]->key,(*((double *)new_d->deviceParams[index]->item)));
                            break;
                        }
                        case slot_param: {
                            if(new_d->slotParams==NULL){
                                new_d->slotParams=malloc(sizeof(Key)*STORAGE_SIZE);
                                memset(new_d->slotParams,0,sizeof (Key)*STORAGE_SIZE);
                            }
                            addToDeviceStorage(out, new_d->slotParams);
                            int index=(hashcode(strlen(out[0]),out[0])%STORAGE_SIZE);
                            printf("\t\tslot data:\n\t\t\tparam_name:%s\n\t\t\tparam_val:%.1lf\n",new_d->slotParams[index]->key,(*((double *)new_d->slotParams[index]->item)));
                            break;
                        }
                        default:
                            break;
                    }
                }

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
               if(strncmp(temp,"[devices]",9)==0) {
                   printf("control:%s\n", temp);
                   getDevices(fileData, &pos);
               }else if(strncmp(temp,"[registers]",11)==0){
                   printf("control:%s\n", temp);
               }else if(strncmp(temp,"[stack]",7)==0){
                   printf("control:%s\n", temp);
               }else{
                   printf("string:%s\n", temp);
               }
            }else{
                char *out[2];
                splitqw(temp,out);
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