#include <stdio.h>
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/readEnviroment.h"
int main() {
/*    TokenNode *list;
    list=Lexer("test_data/tst.txt");
    struct parsetree *start =Parse(&list);
    printTree(start);*/
    readinEniro("test_data/ev_test.ic10e");
    printf("done");
}
