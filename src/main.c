#include <stdio.h>
#include "../include/Lexer.h"
#include "../include/Parser.h"
#include "../include/readEnviroment.h"
#include "../include/debug.h"
#include "../include/tui.h"
#include "../include/executor.h"
int main() {
   /* Enviro *env=readinEniro("../test_data/ev_test.ic10e");
    Debug test;
    test.lists=NULL;
    getKeysEnv(env,&test);*/
    //TokenNode *list;
    //list=Lexer("../test_data/tst.txt");
    //printlex(list);
    //struct parsedata *start =Parse(&list);
    //printTree(start);
    Enviro *env=readinEniro("../test_data/sim.ic10e");
    double d;
    int r=getRegisterData("r4",env,&d);
    printf("rd:%.lf,r:%d\n",d,r);
    printf("done");
}
