#ifndef USER_H_
#define USER_H_

#include "_ATM_.h"
#include <vector>
#include <algorithm>


class User
{
private:

    std::string id;

    std::string pass;

    int balance;

public:

    User();

    ~User();

    void setInfo(std::string _id,std::string _pass);

    void setBalance(int _balance);

    std::string getID();

    std::string getPass();

    bool is_Account_In_Datafile();

    bool is_Login_Successfully(int x,int y);

    int checkBalance(const std::string& path);

    void checkTransHistory(const std::string& path);

    void Deposit(const std::string& path, int moneyDeposit);

    void Withdraw(const std::string& path, int withdraw);

    bool is_ID_In_ListAccount();

    friend void tranfer(User accountTranfer,User accountRecieve, int amount);

    void changePass(std::string newPass);
};



#endif // USER_H_

