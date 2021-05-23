#ifndef showScreen_H
#define showScreen_H

#include "mysupplib.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include "mmsystem.h"

#define RED 12
#define WHITE 15
#define AQUA 11
#define GREEN 10
#define YELLOW 14

void setConsoleScreen(int width, int height);

int showDisplayAndChooseOpt(int x, int y);

int showMenuAndChooseOpt(int x, int y);

int showOptAndChoose(int x,int y,int caseOpt);

void showMusicAndChooseOpt(int x, int y);

#endif // showScreen_H
