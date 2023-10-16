//
// Created by nathan_pc on 10/14/2023.
//

#include "../include/Util.h"
int hashcode(int size,const char *key){
    int prime=31;
    int hash=1;
    for (int i=0;i<size;i++){
        hash=key[i]*prime+hash;
    }
    return hash;
}
int keyhashcode(Key key){
    int prime=31;
    int hash=1;
    for (int i=0;i<key.size;i++){
        hash=key.key[i]*prime+hash;
    }
    return hash;
}

// got this from -> https://stackoverflow.com/questions/21001659/crc32-algorithm-implementation-in-c-without-a-look-up-table-and-with-a-public-li
unsigned int crc32b(unsigned char *message) {
    int i, j;
    unsigned int byte, crc, mask;

    i = 0;
    crc = 0xFFFFFFFF;
    while (message[i] != 0) {
        byte = message[i];            // Get next byte.
        crc = crc ^ byte;
        for (j = 7; j >= 0; j--) {    // Do eight times.
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
        i = i + 1;
    }
    return ~crc;
}