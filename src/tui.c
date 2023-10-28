//
// Created by nathan_pc on 10/18/2023.
//

#include "../include/tui.h"
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
#include "../include/parser.h"
int getconchar( KEY_EVENT_RECORD *krec )
{
    DWORD cc;
    INPUT_RECORD irec;
    HANDLE h = GetStdHandle( STD_INPUT_HANDLE );
    if (h == NULL)
    {
        return 0; // console not found
    }

    for( ; ; )
    {
        ReadConsoleInput( h, &irec, 1, &cc );
        if( irec.EventType == KEY_EVENT &&  (irec.Event).KeyEvent.bKeyDown)
        {
            *krec= irec.Event.KeyEvent;
            return 1;
        }
    }
return 0; //future ????
}
char *getStringfromTree(Statement *data){
    char out[100];
    if(data->stm_expr==NULL) return "";

    switch (data->stm_expr->type) {
        case UNOP:
            sprintf(out,"%s %s %s",
                   data->stm_expr->expr->unop->uop->string,
                   data->stm_expr->expr->unop->uout->string,
                   data->stm_expr->expr->unop->uin1->string);
            break;
        case BINOP:
            sprintf(out,"%s %s %s %s",
                   data->stm_expr->expr->binop->bop->string,
                   data->stm_expr->expr->binop->bout->string,
                   data->stm_expr->expr->binop->bin1->string,
                   data->stm_expr->expr->binop->bin2->string);
            break;
        case TRIOP:
            sprintf(out,"%s %s %s %s %s",
                   data->stm_expr->expr->triop->top->string,
                   data->stm_expr->expr->triop->tout->string,
                   data->stm_expr->expr->triop->tin1->string,
                   data->stm_expr->expr->triop->tin2->string,
                   data->stm_expr->expr->triop->tin3->string);
            break;
        case QUADOP:
            sprintf(out,"%s %s %s %s %s %s",
                   data->stm_expr->expr->quinop->quop->string,
                   data->stm_expr->expr->quadop->qout->string,
                   data->stm_expr->expr->quadop->qin1->string,
                   data->stm_expr->expr->quadop->qin2->string,
                   data->stm_expr->expr->quadop->qin3->string,
                   data->stm_expr->expr->quadop->qin4->string);
            break;
        case QUINOP:
            sprintf(out,"%s %s %s %s %s %s %s",
                   data->stm_expr->expr->quinop->quop->string,
                   data->stm_expr->expr->quinop->quout->string,
                   data->stm_expr->expr->quinop->quin1->string,
                   data->stm_expr->expr->quinop->quin2->string,
                   data->stm_expr->expr->quinop->quin3->string,
                   data->stm_expr->expr->quinop->quin4->string,
                   data->stm_expr->expr->quinop->quin5->string);
            break;
        case SEXOP:
            sprintf(out,"%s %s %s %s %s %s %s %s",
                   data->stm_expr->expr->sexop->sop->string,
                   data->stm_expr->expr->sexop->sout->string,
                   data->stm_expr->expr->sexop->sin1->string,
                   data->stm_expr->expr->sexop->sin2->string,
                   data->stm_expr->expr->sexop->sin3->string,
                   data->stm_expr->expr->sexop->sin4->string,
                   data->stm_expr->expr->sexop->sin5->string,
                   data->stm_expr->expr->sexop->sin6->string);
            break;
        case CMD:
            sprintf(out,"%s %s",
                   data->stm_expr->expr->cmd->cop->string,
                   data->stm_expr->expr->cmd->cin1->string);
            break;
        case LABEL:
            sprintf(out,"%s",data->stm_expr->expr->cmd->cop->string);
            break;
        default:
            sprintf(out,"ERROR reading");
            break;
    }
    char *temp= malloc(strlen(out));
    memset(temp,0,strlen(out));
    strcpy(temp,out);
    return temp;
}
void updateDebug(int curline,struct parsetree *in){
    struct parsetree *data =in;
    printf("\x1b[?25l");
    printf("\x1b[s\x1b[1;1H\x1b(0l\x1b(B");
    for (int i = 1; i < 5; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0w\x1b(B\x1b");
    for (int i = 6; i < 119; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0k\x1b(B\x1b[1E");
    for (int j=1;j<35;j++) {//todo add the scroll to stop at the end of line
        char *hl=( j==(curline+1) && (curline+1)<=18)? "7":"0";
        hl=(j==18&& (curline+1)>=18)? "7":hl;
        hl=(j==(curline+1) && (curline+1)>=data->lines+1)? "7":hl;
        int line=((curline+1)<=17)? 0 : curline-17;
        line=((curline)>=data->lines)? -1 : line;
        char *code =getStringfromTree(&data->line_table[line+j-1]);
        code=(line<0)? "" :code;
        printf("\x1b[2K\x1b(0x\x1b(B"
               "%d"//line numbers
               "\x1b[6G\x1b(0x\x1b(B"
               "\x1b[%sm"
               "%s"
               "\x1b[0m"//code
               "\x1b(0\x1b[120Gx\x1b(B\x1b[1E",line+j-1,hl,code);
    }
    printf("\x1b(0t\x1b(B");

    for (int i = 1; i < 5; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0v\x1b(B\x1b");
    for (int i = 6; i < 119; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0u\x1b(B\x1b[1E");

    for (int j=35;j<51;j++) {//stack ans register area
        printf("\x1b(0x\x1b[120Gx\x1b(B\x1b[1E");
    }

    printf("\x1b(0m\x1b(B");
    for (int i = 1; i < 119; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0j\x1b(B\x1b[u");
    printf("\x1b[?25h");
}
int test(){
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    dwMode |= DISABLE_NEWLINE_AUTO_RETURN;
    COORD size,old;
    SMALL_RECT box;
    box.Bottom=49;
    box.Right=119;
    box.Top=0;
    box.Left=0;
    size.X=120;
    size.Y=50;
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    SetConsoleScreenBufferSize(hOut,size);
    SetConsoleWindowInfo(hOut,1,&box);
    SetConsoleMode(hOut, dwMode);
    printf("\x1b[2 q");
    old=info.dwSize;
    KEY_EVENT_RECORD key;
    int line=0;
    TokenNode *list;
    list=Lexer("../test_data/tst.txt");
    struct parsetree *start =Parse(&list);
    updateDebug(line,start);
    int stop=1;
    while(stop){
        SetConsoleWindowInfo(hOut,1,&box);
        GetConsoleScreenBufferInfo(hOut, &info);
        printf("\x1b[s\x1b[49;108H\x1b[31mX:%hi,Y:%hi\x1b[u\x1b[0m",info.dwCursorPosition.X+1,info.dwCursorPosition.Y+1);
        getconchar( &key);
        switch (key.wVirtualKeyCode) {
            case VK_UP:{
                wprintf(L"\x1B[1A");
                break;
            }
            case VK_DOWN:{
                wprintf(L"\x1B[1B");
                break;
            }
            case VK_LEFT:{
                wprintf(L"\x1B[1D");
                break;
            }
            case VK_RIGHT:{
                wprintf(L"\x1B[1C");
                break;
            }
            case VK_F1:{
                GetConsoleScreenBufferInfo(hOut, &info);
                printf("\x1b[36mX:%hi,Y:%hi\x1b[0m",info.dwCursorPosition.X,info.dwCursorPosition.Y);
                break;
            }
            case VK_F2:{
                wprintf(L"\x1B[2J\x1B[3J");//<<<clears the screen
                break;
            }
            case VK_F3:{
                line++;
                updateDebug(line,start);
                break;
            }
            case VK_ESCAPE:{
                stop=0;
                break;
            }
            case VK_RETURN:{
                wprintf(L"\x1b[32mhello\x1b[0m");
                break;
            }
        }
    }
    SetConsoleScreenBufferSize(hOut,old);
    wprintf(L"\x1B[2J\x1B[3J");
    printf("printing tree\n");
    printTree(start);
    printf("\n\nprinting lex\n");
    printlex(list);
}
