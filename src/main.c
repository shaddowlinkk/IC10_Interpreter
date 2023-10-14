#include <stdio.h>
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/Data_structs.h"
int main() {
    TokenNode *list;
    list=Lexer("test_data/tst.txt");
    struct parsetree *start =Parse(&list);
    printTree(start);
    printf("done");
}
