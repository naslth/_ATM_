#ifndef mysupplib_H_
#define mysupplib_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <map>
#include <ctime>

void setColor(int numcolor);

void gotoXY(SHORT x,SHORT y);

void setConsoleSize(SHORT width, SHORT height);

void setConsoleScreenBufferSize(SHORT width, SHORT height);

void ShowCur(bool is_show);

std::string getCurrentTime();


#endif // mysupplib_H_
