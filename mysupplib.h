#ifndef mysupplib_H_
#define mysupplib_H

#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

void setColor(int numcolor);
void gotoXY(SHORT x,SHORT y);
void setConsoleSize(SHORT width, SHORT height);
void setConsoleScreenBufferSize(SHORT width, SHORT height);
std::string maskingPass();
void ShowCur(bool is_show);

#endif // mysupplib_H_
