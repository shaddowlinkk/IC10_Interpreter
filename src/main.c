#include <stdio.h>
//#include "../include/Lexer.h"
//#include "../include/Parser.h"
#include "../include/readEnviroment.h"
#include "../include/tui.h"
int main() {
    //readinEniro("../test_data/ev_test.ic10e");
    TokenNode *list;
    list=Lexer("../test_data/test.txt");
    struct parsedata *start =Parse(&list);
    printTree(start);
    printf("done");
}
