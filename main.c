#include <stdio.h>
#include "Lexer.h"
#include "Parser.h"
#include "Data_structs.h"
int main() {
    TokenNode *list;
    list=Lexer("tst.txt");
    struct parsetree *start =Parse(&list);
    printTree(start);
    printf("done");
}
