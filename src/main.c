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
    TokenNode *list;
    list=Lexer("../test_data/test.txt");
    printlex(list);
    struct parsedata *start =Parse(&list);
    start->trace=&start->stmt;
    printTree(start);
    Enviro *env=readinEniro("../test_data/sim.ic10e");
/*    double r=getRegisterData("1",env,start);
    printf("rd:%.1lf\n",r);
    execute_stmt(&start->stmt,env,start);
     r=getRegisterData("r0",env,start);
    printf("rd:%.1lf\n",r);*/
    while ((*start->trace)->statement!=NULL){
        start->trace=&(*start->trace)->statement;
    }
    execute_stmt(env,start);
    printf("done");
}
