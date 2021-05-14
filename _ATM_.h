#ifndef _ATM_H_
#define _ATM_H_

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct user
{
    string id;
    string pass;
    map<int,int> value;
    user() {};
    user(string _id, string _pass)
    {
        id=_id;
        pass=_pass;
        value[10000]=0;
        value[20000]=0;
        value[50000]=0;
        value[100000]=0;
        value[200000]=0;
        value[500000]=0;
    }
    void logIn();
};

bool is_ID_Valid(string id);
bool is_Pass_Valid(string pass);
bool is_Account_In_File(user test,const string& path);
bool is_Login_Successfully(user test);
void showMenu();
map<int,int> readDataFromFileToMap(const string& path);
void writeDataFromMapToFile(map<int,int> _map, const string& path);
int checkBalance(user test,const string& path);
void checkTransHistory(const string& path);
void changePass(string usernameNeedToChangePass, string newPass);
void tranfer(string accountTransferFrom, string accountTransferTo);

#endif // _ATM_H_
