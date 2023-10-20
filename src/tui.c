//
// Created by nathan_pc on 10/18/2023.
//

#include "../include/tui.h"
#include <windows.h>
#include <wchar.h>
#include <stdio.h>
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

void updateDebug(int curline){
    printf("\x1b[?25l");
    printf("\x1b[s\x1b[1;1H\x1b(0l\x1b(B");
    for (int i = 1; i < 5; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0w\x1b(B\x1b");
    for (int i = 6; i < 119; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0k\x1b(B\x1b[1E");

    for (int j=1;j<35;j++) {
       /* char *hl=( j==curline && j!=18)? "30;97":"27";
        hl=( j!=curline && j!=18)? "30;97":"27";*/
        printf("\x1b(0x\x1b(B"
               "%d"//line numbers
               "\x1b[6G\x1b(0x\x1b(B"
               "\x1b[%sm"
               "%s"
               "\x1b[27m"//code
               "\x1b(0\x1b[120Gx\x1b(B\x1b[1E",curline+j-1,"","test");
    }

    printf("\x1b(0t\x1b(B");

    for (int i = 1; i < 5; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0v\x1b(B\x1b");
    for (int i = 6; i < 119; i++)printf("\x1b(0q\x1b(B");
    printf("\x1b(0u\x1b(B");

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
    dwMode |=DISABLE_NEWLINE_AUTO_RETURN;
    COORD size;
    SMALL_RECT box;
    box.Bottom=49;
    box.Right=119;
    box.Top=0;
    box.Left=0;
    size.X=120;
    size.Y=50;
    SetConsoleScreenBufferSize(hOut,size);
    SetConsoleWindowInfo(hOut,1,&box);
    SetConsoleMode(hOut, dwMode);
    printf("\x1b[2 q");
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(hOut, &info);
    KEY_EVENT_RECORD key;
    int line=0;
    updateDebug(line);
    while(1){
        SetConsoleWindowInfo(hOut,1,&box);
        GetConsoleScreenBufferInfo(hOut, &info);
        printf("\x1b[s\x1b[49;108H\x1b[31mX:%hi,Y:%hi\x1b[u\x1b[27m",info.dwCursorPosition.X+1,info.dwCursorPosition.Y+1);
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
                printf("\x1b[36mX:%hi,Y:%hi\x1b[27m",info.dwCursorPosition.X,info.dwCursorPosition.Y);
                break;
            }
            case VK_F2:{
                wprintf(L"\x1B[2J\x1B[3J");//<<<clears the screen
                break;
            }
            case VK_F3:{
                line++;
                updateDebug(line);
                break;
            }
            case VK_RETURN:{
                wprintf(L"\x1b[32mhello\x1b[27m");
                break;
            }
        }
    }
}
