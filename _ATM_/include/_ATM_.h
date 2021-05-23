#ifndef _ATM_H_
#define _ATM_H_

#include "mysupplib.h"
#include <vector>
#include <algorithm>

using namespace std;

class User
{
private:

    string id;

    string pass;

    int balance;

public:

    User();

    ~User();

    void setInfo(string _id,string _pass);

    void setBalance(int _balance);

    string getID();

    string getPass();

    bool is_Account_In_Datafile();

    bool is_Login_Successfully(int x,int y);

    int checkBalance(const string& path);

    void checkTransHistory(const string& path);

    void Deposit(const string& path, int moneyDeposit);

    void Withdraw(const string& path, int withdraw);

    bool is_ID_In_ListAccount();

    friend void tranfer(User accountTranfer,User accountRecieve, int amount);

    void changePass(string newPass);
};



#endif // _ATM_H_
