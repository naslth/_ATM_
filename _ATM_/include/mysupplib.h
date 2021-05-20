#ifndef mysupplib_H_
#define mysupplib_H

#include <iostream>
#include <fstream>
#include <windows.h>
#include <conio.h>
#include <string>
#include <map>

void setColor(int numcolor);

void gotoXY(SHORT x,SHORT y);

void setConsoleSize(SHORT width, SHORT height);

void setConsoleScreenBufferSize(SHORT width, SHORT height);

void ShowCur(bool is_show);

std::string maskingPass();

void writeDataFromMapToFile(std::map<int,int> _map, const std::string& path);

std::map<int,int> readDataFromFileToMap(const std::string& path);

void updateBalanceInFile(const std::string& path,int newBalance);

#endif // mysupplib_H_
