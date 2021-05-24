#include "../include/mysupplib.h"


void setColor(int numColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),numColor);
}



void gotoXY(SHORT x,SHORT y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}



void setConsoleSize(SHORT width, SHORT height)
{
    SMALL_RECT Console;
    Console.Top = 0;
    Console.Left = 0;
    Console.Bottom = height-1;
    Console.Right = width-1;
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), 1, &Console);
}



void setConsoleScreenBufferSize(SHORT width, SHORT height)
{
    COORD c;
    c.X = width;
    c.Y = height;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), c);
}



void ShowCur(bool is_show)
{
    CONSOLE_CURSOR_INFO CurInf;
    CurInf.dwSize = 10;
    CurInf.bVisible = is_show;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInf);
}


std::string getCurrentTime() {
    time_t timeNow = time(0);
    std::string dt = ctime(&timeNow);
    return dt;
}




