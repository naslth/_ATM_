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

bool is_ID_Valid(std::string id);

bool is_Pass_Valid(std::string pass);

std::string maskingPass();

void writeDataFromMapToFile(std::map<int,int> _map, const std::string& path);

std::map<int,int> readDataFromFileToMap(const std::string& path);

void updateBalanceInFile(const std::string& path,int newBalance);

void goBack();


#endif // mysupplib_H_
