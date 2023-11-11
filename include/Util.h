//
// Created by nathan_pc on 10/14/2023.
//

#ifndef IC10_INTERPRETER_UTIL_H
#define IC10_INTERPRETER_UTIL_H
typedef struct _key{
    int size;
    char *key;
    void *item;
    struct _key *next;
}Key;
int keyhashcode(Key key);
int hashcode(int size,const char *key);
unsigned int crc32b(const unsigned char *message);

#endif //IC10_INTERPRETER_UTIL_H
