//
// Created by nathan_pc on 10/14/2023.
//

#ifndef IC10_INTERPRETER_UTIL_H
#define IC10_INTERPRETER_UTIL_H
typedef struct _key{
    int size;
    char key[32];
    void *item;
    struct _key *next;
}Key;
int hashcode(Key key);

#endif //IC10_INTERPRETER_UTIL_H
