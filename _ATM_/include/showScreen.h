#ifndef showScreen_H
#define showScreen_H

#include "mysupplib.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

#define RED 12
#define WHITE 7

void setConsoleScreen(int width, int height);

int showDisplayAndChooseOpt(int x, int y);

int showMenuAndChooseOpt(int x, int y);

int showOptAndChoose(int x,int y,int caseOpt);


#endif // showScreen_H
