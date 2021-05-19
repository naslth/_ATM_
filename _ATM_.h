#ifndef _ATM_H_
#define _ATM_H_

#include "mysupplib.h"
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct User
{
    string id;
    string pass;
    int balance;

};

bool is_ID_Valid(string id);
bool is_Pass_Valid(string pass);
bool is_Account_In_File(User test,const string& path);
bool is_Login_Successfully(User test);
int showDisplayAndChooseOpt(int x, int y);
int showMenuAndChooseOpt(int x, int y);
int showOptAndChoose(int x,int y,int caseOpt);
map<int,int> readDataFromFileToMap(const string& path);
void writeDataFromMapToFile(map<int,int> _map, const string& path);
int checkBalance(const string& path);
void checkTransHistory(const string& path);
void Deposit(const string& path, User test, int moneyDeposit);
void Withdraw(const string& path, User test, int withdraw);
bool is_ID_In_ListAccount(string ID);
void tranfer(string accountTransfer, string accountReceive,int accountTransferBalance, int amount);
void changePass(string usernameNeedToChangePass, string newPass);

#endif // _ATM_H_
