#include "mysupplib.h"

void setColor(int numColor)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),numColor);
}
void gotoXY(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
std::string maskingPass() {
    char temp;
    std::string maskedPass="";
    while((temp=_getch()) != '\r') {
        if(temp!='\b'){
            std::cout << "*";
            maskedPass+=temp;
        }
        else {
            std::cout << "\b" << " " << "\b";
            maskedPass.pop_back();
        }
    }
    return maskedPass;
}
