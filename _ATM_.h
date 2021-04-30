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

struct user {
    int ordinalNumber;
    string id;
    string pass;
    map<int,int> value;
    user() {};
    user(string _id, string _pass) {
        ordinalNumber=0;
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
    bool checkAccount(const string& path);
};
bool logInsuccessfully(user test);
void showMenu();
int checkBalance(user test);


#endif // _ATM_H_
