//
// Created by nathan_pc on 10/15/2023.
//

#include "../include/readEnviroment.h"
#include "../include/Util.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define STORAGE_SIZE 512
#define DEFAULT_DEVICES 10
//todo make sure that no  bad data can come into the system from reading ic10e files
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
}
void addToDeviceStorage(char ** data, Key **storage){

    double con = strtod(data[1],NULL);
    Key *newKey= malloc(sizeof(Key));
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

Device *InitDevice(){
    Device *new_d = malloc(sizeof(Device));
    new_d->deviceParams=NULL;
    new_d->slotParams=NULL;
    new_d->deviceSettings=NULL;
    new_d->name=NULL;
    new_d->name_size=0;
    return new_d;
}

Device **getDevices(char *data,int *pos,int devs){
    Device **device_list= malloc(sizeof(Device )*devs);
    memset(device_list,0,sizeof(Device )*devs);
    Device *new_d = InitDevice();
    int device=0;
    enum device_storage{settings,param,slot_param};
    int currstate=0;
    while (!(data[*pos]=='}' && data[((*pos)+1)]!=',')) {
        if((data[*pos]=='}' && data[((*pos)+1)]==',')) {
            printf("\tnext\n");
            device_list[device]=new_d;
            device++;
            new_d = InitDevice();
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
                            printf("\t\tdevice setting:\n\t\t\tparam_name:%s\n\t\t\tparam_val:%.1lf\n",new_d->deviceSettings[index]->key,(*((double *)new_d->deviceSettings[index]->item)));
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
    device_list[device]=new_d;
    *pos=(*pos)+1;
    return device_list;
}
Enviro *proccesFile(char *fileData,int size){
    Enviro *out = malloc(sizeof(Enviro));
    memset(out->regs,0, sizeof(double )*18);
    memset(out->stack,0, sizeof(double )*512);
    out->tree=NULL;
    out->numdevs=-1;
    int pos=0;
    enum data_type{reg,stack,info};
    int type=0;
    while (fileData[pos]!='\0') {
        if (fileData[pos]!='\t') {
            char *temp = GetNextEniroString(fileData, &pos);
            if(temp[0]=='['){
               if(strncmp(temp,"[devices]",9)==0) {
                   printf("control:%s\n", temp);
                   int num =(out->numdevs>-1)? out->numdevs:DEFAULT_DEVICES;
                   out->devices=getDevices(fileData, &pos,num);
               }else if(strncmp(temp,"[registers]",11)==0){
                   type=reg;
                   printf("control:%s\n", temp);
               }else if(strncmp(temp,"[stack]",7)==0){
                   type=stack;
                   printf("control:%s\n", temp);
               }else if(strncmp(temp,"[envinfo]",7)==0){
                   type=info;
                   printf("control:%s\n", temp);
               }else{
                   printf("string:%s\n", temp);
               }
            }else{
                char *split[2];
                splitqw(temp,split);
                switch (type) {
                    case reg:{
                        if(split[0][1]>='0' &&split[0][1]<='9') {
                            split[0]++;
                            char *idx= malloc(sizeof (char*));
                            strcpy(idx,split[0]);
                            out->regs[strtol(idx,NULL,0)] = strtod(split[1],NULL);
                            printf("\t reg:%d\n\t\tval:%.1lf\n",(int)strtol(idx,NULL,0),out->regs[strtol(idx,NULL,0)]);
                            free(idx);
                        }

                        break;
                    }
                    case stack:{
                        if(split[0][0]>='0' &&split[0][0]<='9') {
                            char *idxs= malloc(sizeof (char*));
                            strcpy(idxs, split[0]);
                            out->stack[strtol(idxs,NULL,0)] = strtod(split[1], NULL);
                            printf("\t stack:%ld\n\t\tval:%.1lf\n", strtol(idxs,NULL,0),out->stack[strtol(idxs,NULL,0)]);
                            free(idxs);
                        }
                        break;
                    }
                    case info:{
                        if(strcmp(split[0],"devicenum")==0){
                            out->numdevs= strtol(split[1],NULL,0);
                        }
                        break;
                    }
                    default:
                        break;
                }
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