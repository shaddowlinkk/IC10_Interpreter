//
// Created by nathan_pc on 11/2/2023.
//

#ifndef IC10_INTERPRETER_DEBUG_H
#define IC10_INTERPRETER_DEBUG_H
struct devicelist{
    char *DeviceSetting[512];
    char *Deviceparam[512];
    struct devicelist *next;
};
struct hashKeylist{
    char *lable[512];
    struct devicelist *list;
};
typedef struct _debug{
    struct hashKeylist lists;
}Debug;

#endif //IC10_INTERPRETER_DEBUG_H
