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

int test(){
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    dwMode |=DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode(hOut, dwMode);
    printf("\x1b[2 q");
    printf("\x1B[34mtest\r\n");
    wprintf(L"\x1B[32mtest\x1B[39m\r\n");
    CONSOLE_SCREEN_BUFFER_INFO info;
    KEY_EVENT_RECORD key;
    while(1){

        GetConsoleScreenBufferInfo(hOut, &info);
        printf("\x1b[s\x1b[30;111H\x1b[31mX:%hi,Y:%hi\x1b[u",info.dwCursorPosition.X,info.dwCursorPosition.Y);
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
                printf("\x1b[36mX:%hi,Y:%hi",info.dwCursorPosition.X,info.dwCursorPosition.Y);
                break;
            }
            case VK_F2:{
                wprintf(L"\x1B[2J\x1B[3J");//<<<clears the screen
                break;
            }
            case VK_RETURN:{
                wprintf(L"\x1b[32mhello");
                break;
            }
        }
    }
}
