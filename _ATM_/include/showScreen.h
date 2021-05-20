#ifndef showScreen_H
#define showScreen_H

#include <iostream>
#include <windows.h>
#include <conio.h>


void setConsoleScreen(int width, int height);

int showDisplayAndChooseOpt(int x, int y);

int showMenuAndChooseOpt(int x, int y);

int showOptAndChoose(int x,int y,int caseOpt);


#endif // showScreen_H
