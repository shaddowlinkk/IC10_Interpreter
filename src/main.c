#include <stdio.h>
#include <time.h>
#include <Windows.h>
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
    list=Lexer("../test_data/ltest.txt");
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
/*    int test = checkForDeviceConnected(env,70);
    printf("found device:%d\n",test);*/
//todo at 1000 lines it start acting weird but after 1000 it if ok?
    clock_t t;
    t = clock();
    printf("mips started\n");
    while ((*start->trace)!=NULL){
       printf("linenumber:%d\n",(*start->trace)->line);
        execute_stmt(env,start);

    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds

    printf("mips took %f seconds to execute \n", time_taken);
    printRegisters(env);
    printf("done\n");
}
