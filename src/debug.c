//
// Created by nathan_pc on 11/2/2023.
//

#include "../include/debug.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
struct devicelist *newlist(){
    struct devicelist *list = malloc(sizeof(struct devicelist));
    list->next=NULL;
    memset(list->Deviceparam,0,sizeof(char *)*STORAGE_SIZE);
    memset(list->DeviceSetting,0, sizeof(char *)*STORAGE_SIZE);
    return list;
}
void getkeys(char **list, Key **hashmap){
    int curindex=0;
    for (int i = 0; i < STORAGE_SIZE; ++i) {
        if(hashmap[i]!=NULL){
            list[curindex]=hashmap[i]->key;
            curindex++;
        }
    }
}
void getKeysEnv(Enviro *env,Debug *out){
    for (int i = 0; i < env->numdevs; ++i) {
        if(env->devices[i]!=NULL) {
            struct devicelist *new_L = newlist();
            getkeys(new_L->DeviceSetting, env->devices[i]->deviceSettings);
            getkeys(new_L->Deviceparam, env->devices[i]->deviceParams);
            struct devicelist **trace = &out->lists;
            while ((*trace)) {
                trace = &(*trace)->next;
            }
            new_L->next = (*trace);
            (*trace) = new_L;
        }
    }

}