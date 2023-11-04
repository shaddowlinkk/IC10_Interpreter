#include <stdio.h>
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/readEnviroment.h"
#include "../include/debug.h"
#include "../include/tui.h"
int main() {
    Enviro *env=readinEniro("../test_data/ev_test.ic10e");
    Debug test;
    test.lists=NULL;
    getKeysEnv(env,&test);
/*    TokenNode *list;
    list=Lexer("../test_data/tst.txt");
    printlex(list);
    struct parsedata *start =Parse(&list);
    printTree(start);*/
    printf("done");
}
