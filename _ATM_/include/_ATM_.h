#ifndef _ATM_H_
#define _ATM_H_

#include "mysupplib.h"
#include "User.h"

void signUp(std::string tempID, std::string tempPass);

bool is_ID_Valid(std::string id);

bool is_Pass_Valid(std::string pass);

std::string maskingPass();

void writeDataFromMapToFile(std::map<int,int> _map, const std::string& path);

std::map<int,int> readDataFromFileToMap(const std::string& path);

void updateBalanceInFile(const std::string& path,int newBalance);

void goBack();

#endif // _ATM_H_
