//
// Created by nathan_pc on 10/14/2023.
//

#include "../include/Util.h"
int hashcode(Key key){
    int prime=31;
    int hash=1;
    for (int i=0;i<key.size;i++){
        hash=key.key[i]*prime+hash;
    }
    return hash;
}
