#include <stdio.h>
#include "../Include/Lexer.h"
#include "../Include/Parser.h"
#include "../Include/Data_structs.h"
int main() {
    TokenNode *list;
    list=Lexer("test_data/tst.txt");
    struct parsetree *start =Parse(&list);
    printTree(start);
    printf("done");
}
