#include"_ATM_.h"
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    const int moneyArr[6]={10000,20000,50000,100000,200000,500000};
    DISPLAY:
    cout << "   THIS IS MY ATM!!    " << "\n";
    cout << "Do you have an account?" << "\n";
    cout << "1. Yes, I have an account" << "\n";
    cout << "2. No, not yet" << "\n";
    cout << "3. Exit" << "\n";
    cout << "Choose your answer: ";
    int answer;
    cin >> answer;
    while(answer!=1&&answer!=2&&answer!=3) {
        cout << "Your answer is invalid. Please choose another answer!" << "\n";
        cin >> answer;
    }
    if(answer==1) cout << "Please log in to your account." << "\n";
    else if(answer==2) {
        string accountInfo="";
        user temp("0","0");
        fstream fileListAccount;
        fileListAccount.open("listAccount.txt",ios_base::in | ios_base::out | ios_base::app);
        if(fileListAccount.is_open()) {
            cout << "Please register here:" << "\n";
            cout << "Your ID is: ";
            cin >> temp.id;
            user temp2("0","0");
            bool check=true;
            while(true) {
                while (!fileListAccount.eof()) {
                fileListAccount >> temp2.id;
                fileListAccount >> temp2.pass;
                if(temp2.id == temp.id) {
                    check=false;
                }
                for(int i=0;i<6;i++) {
                    int x;
                    fileListAccount >> x;
                }
                }
                if(check==false) {
                    check=true;
                    cout << "Your ID is already exist. Please try again!" << "\n";
                    cout << "Your ID is: ";
                    cin >> temp.id;
                    fileListAccount.clear();
                    fileListAccount.seekg(0, ios_base::beg);
                }
                else if(check==true) {
                    fileListAccount.seekp(0, ios_base::end);
                    break;
                }
            }
            fileListAccount.clear();
            fileListAccount << temp.id << "\n";
            cout << "Your ID is valid." << "\n";
            cout << "Your password is: " << "\n";
            cin >> temp.pass;
            cout << "Confirm your password:" << "\n";
            string passcf;
            cin >> passcf;
            while(passcf!=temp.pass) {
                cout << "Password confirmation does not match. Try again!" << "\n";
                cout << "Your password is: " << "\n";
                cin >> temp.pass;
                cout << "Confirm your password:" << "\n";
                cin >> passcf;
            }
            fileListAccount << temp.pass << "\n";
            cout << "Sign up success. Please log in to your account." << "\n";
            accountInfo=temp.id;
        }
        else cout << "Can't open file.";
        fileListAccount.close();
        ofstream fileAccountInfo;
        fileAccountInfo.open(accountInfo,ios_base::out);
        if(fileAccountInfo.is_open()) {
            map<int,int>::iterator i;
            for (i = (temp.value).begin(); i != (temp.value).end(); i++) {
                fileAccountInfo << (i->second) << "\n";
            }
        }
        else cout << "Can't open file.";
        fileAccountInfo.close();
    }
    else if(answer==3) return 0;
    user test;
    test.logIn();
    if(logInsuccessfully(test)) {
        map<int,int> ATM_money;
        map<int, int>::iterator i;
        for(int j=0;j<6;j++) {
            ATM_money[moneyArr[j]]=0;
        }
        cout << "Log in successfully!" << "\n";
        string accountInfo=test.id;
        DOSOMETHINGWHENYOULOGIN:
        int menuOpt;
        do {
            showMenu();
            cin >> menuOpt;
            while(menuOpt<1||menuOpt>5) {
                cout << "Invalid selection. Please choose another option: ";
                cin >> menuOpt;
            }
            switch(menuOpt)
            {
                case 1: {
                    cout << "This is your transaction history: " << "\n";
                    ifstream fileAccountIn;
                    fileAccountIn.open(accountInfo,ios_base::in);
                    if(fileAccountIn.is_open()) {
                        int numsofMoney[6];
                        for(int i=0;i<6;i++) {
                            fileAccountIn >> numsofMoney[i];
                        }
                        while(fileAccountIn.eof()) {
                            string temp;
                            getline(fileAccountIn,temp);
                            cout << temp << "\n";
                        }
                    }
                    else cout << "Can't open file.";
                    fileAccountIn.close();
                    break;
                }
                case 2:{
                    int balance;
                    balance=checkBalance(test);
                    cout << "Your balance is: " << balance << " VND." << "\n";
                    break;
                }
                case 3: {
                    int dOpt;
                    BACKTOCASE3:
                    cout << "Choose an option: " << "\n";
                    cout << "1. Deposit         2. Exit";
                    cin >> dOpt;
                    while(dOpt<1||dOpt>2) {
                        cout << "Invalid selection. Please choose another option: ";
                        cin >> dOpt;
                    }
                    if(dOpt==1){
                        int denominations;
                        int bills;
                        cout << "Enter the denominations: ";
                        cin >> denominations;
                        cout << "Enter the bills: ";
                        cin >> bills;
                        ifstream fileAccountIn;
                        fileAccountIn.open(accountInfo,ios_base::in);
                        if(fileAccountIn.is_open()) {
                            for (i = (test.value).begin(); i != (test.value).end(); i++) {
                                fileAccountIn >> (i->second);
                            }
                        }
                        else cout << "Can't open file." << "\n";
                        fileAccountIn.close();
                        for (i = (test.value).begin(); i != (test.value).end(); i++) {
                            if((i->first)==denominations) (i->second)+=bills;
                        }
                        ofstream fileAccountOut;
                        fileAccountOut.open(accountInfo,ios_base::out);
                        if(fileAccountOut.is_open()) {
                            int j=0;
                            for (i = (test.value).begin(); i != (test.value).end(); i++,j++) {
                                if(moneyArr[j]==denominations) {
                                    fileAccountOut.seekp(j, ios_base::beg);
                                    fileAccountOut << (i->second);
                                }
                            }
                        }
                        else cout << "Can't open file." << "\n";
                        fileAccountOut.close();
                        fileAccountOut.open(accountInfo,ios_base::app);
                        if(fileAccountOut.is_open()) {
                            fileAccountOut << "You have deposited " << bills*denominations << " VND." << "\n";
                        }
                        else cout << "Can't open file." << "\n";
                        fileAccountOut.close();
                        int currentBalance=checkBalance(test);
                        cout << "Deposit successfully. Your current balance is: " << currentBalance << " VND" << "\n";
                        fstream fileATM;
                        fileATM.open("ATMinfo.txt",ios_base::in | ios_base::out);
                        if(fileATM.is_open()) {
                            fileATM.seekg(0, ios_base::beg);
                            for (i = ATM_money.begin(); i != ATM_money.end(); i++) {
                                fileATM >> (i->second);
                            }
                            for (i = ATM_money.begin(); i != ATM_money.end(); i++) {
                                if((i->first)==denominations) (i->second)+=bills;
                            }
                            fileATM.clear();
                            fileATM.seekp(0, ios_base::beg);
                            for (i = ATM_money.begin(); i != ATM_money.end(); i++) {
                                fileATM << i->second << "\n";
                            }
                            fileATM.clear();
                        }
                        else cout << "Can't open file.";
                        fileATM.close();
                        goto BACKTOCASE3;
                    }
                    if(dOpt==2) break;
                }
                case 4: {
                    ifstream fileATM;
                    fileATM.open("ATMinfo.txt",ios_base::in);
                    if(fileATM.is_open()) {
                        for (i = ATM_money.begin(); i != ATM_money.end(); i++) {
                            fileATM >> (i->second);
                        }
                    }
                    else cout << "Can't open file.";
                    fileATM.close();
                    ifstream fileAccountIn;
                    fileAccountIn.open(accountInfo,ios_base::in);
                    if(fileAccountIn.is_open()) {
                        for (i = (test.value).begin(); i != (test.value).end(); i++) {
                            fileAccountIn >> (i->second);
                        }
                    }
                    else cout << "Can't open file." << "\n";
                    fileAccountIn.close();
                    int minwithdraw;
                    for (i = ATM_money.begin(); i != ATM_money.end(); i++) {
                        if((i->second)!=0) minwithdraw=(i->first);
                    }
                    BACKTOCASE4:
                    int balance,withdraw;
                    balance=checkBalance(test);
                    cout << "Your balance is: " << balance << " VND." << "\n";
                    cout << "How much do you want to withdraw?" << "\n";
                    cin >> withdraw;
                    if(withdraw<minwithdraw) {
                        cout << "The smallest amount that can be withdrawn is: " << minwithdraw << " . Please try again!" << "\n";
                        goto BACKTOCASE4;
                    }
                    else if(withdraw%minwithdraw!=0) {
                        cout << "Not enough change to withdraw! The withdrawal amount must be a multiple of " << minwithdraw << " . Please try again!" << "\n";
                        goto BACKTOCASE4;
                    }
                    else if((balance-withdraw)<50000) {
                        cout << "Not enough balance for withdrawal! Please try again!" << "\n";
                        goto BACKTOCASE4;
                    }
                    else {
                        if((withdraw%500000==0) && (ATM_money[500000]>(withdraw/500000))) {
                            ATM_money[500000]-=(withdraw/500000);
                            test.value[500000]-=(withdraw/500000);
                            ofstream fileAccountOut;
                            fileAccountOut.open(accountInfo,ios_base::out);
                            if(fileAccountOut.is_open()) {
                                int j=0;
                                for (i = (test.value).begin(); i != (test.value).end(); i++,j++) {
                                    if(moneyArr[j]==500000) {
                                        fileAccountOut.seekp(j, ios_base::beg);
                                        fileAccountOut << (i->second);
                                    }
                                }
                            }
                            else cout << "Can't open file." << "\n";
                            fileAccountOut.close();
                            ofstream fileATMOut;
                            fileATMOut.open("ATMinfo.txt",ios_base::out);
                            if(fileATMOut.is_open()) {
                                int j=0;
                                for (i = ATM_money.begin(); i != ATM_money.end(); i++,j++) {
                                    if(moneyArr[j]==500000) {
                                        fileATMOut.seekp(j, ios_base::beg);
                                        fileATMOut << (i->second);
                                    }
                                }
                            }
                            else cout << "Can't open file." << "\n";
                            fileATMOut.close();
                            fileAccountOut.open(accountInfo,ios_base::app);
                            if(fileAccountOut.is_open()) {
                                fileAccountOut << "You have withdrawn " << withdraw << " VND." << "\n";
                            }
                            else cout << "Can't open file." << "\n";
                            fileAccountOut.close();
                            cout << "Successful withdrawal!" << "\n";
                            cout << "The number of 500000 VND bills is: " << withdraw/500000 << "\n";
                            int currentBalance=checkBalance(test);
                            cout << "Your current balance is: " << currentBalance << " VND." << "\n";
                            goto BACKTOCASE4;
                        }
                        else {
                            vector<int> atmCheckList;
                            for (int j = 5; j >= 0; j--) {
                                int atmCheck = min(withdraw / moneyArr[j], ATM_money[moneyArr[j]]);
                                withdraw -= atmCheck * moneyArr[j];
                                atmCheckList.push_back(atmCheck);
                                if (withdraw == 0) {
                                    if(atmCheckList.size()<6) {
                                        for(int j=atmCheckList.size()-1;j<6;j++) {
                                            atmCheckList.push_back(0);
                                        }
                                    }
                                    reverse(atmCheckList.begin(),atmCheckList.end());
                                    for(int j=0;j<6;j++) {
                                        ATM_money[moneyArr[j]]-=atmCheckList[j];
                                    }
                                    for(int j=0;j<6;j++) {
                                        test.value[moneyArr[j]]-=atmCheckList[j];
                                    }
                                    ofstream fileAccountOut;
                                    fileAccountOut.open(accountInfo,ios_base::out);
                                    if(fileAccountOut.is_open()) {
                                        int j=0;
                                        for (i = (test.value).begin(); i != (test.value).end(); i++,j++) {
                                            fileAccountOut.seekp(j, ios_base::beg);
                                            fileAccountOut << (i->second);
                                        }
                                    }
                                    else cout << "Can't open file." << "\n";
                                    fileAccountOut.close();
                                    ofstream fileATMOut;
                                    fileATMOut.open("ATMinfo.txt",ios_base::out);
                                    if(fileATMOut.is_open()) {
                                        for (i = ATM_money.begin(); i != ATM_money.end(); i++) {
                                            fileATMOut << i->second << "\n";
                                        }
                                    }
                                    else cout << "Can't open file." << "\n";
                                    fileATMOut.close();
                                    fileAccountOut.open(accountInfo,ios_base::app);
                                    if(fileAccountOut.is_open()) {
                                        fileAccountOut << "You have withdrawn " << withdraw << " VND." << "\n";
                                    }
                                    else cout << "Can't open file." << "\n";
                                    fileAccountOut.close();
                                    cout << "Successful withdrawal!" << "\n";
                                    for (int j = 5; j >= 0; j--) {
                                    cout << "The number of " << moneyArr[j] <<" VND bills is: " << atmCheckList[j] << endl;
                                    }
                                    int currentBalance=checkBalance(test);
                                    cout << "Your current balance is: " << currentBalance << " VND." << "\n";
                                    goto BACKTOCASE4;
                                }
                            }
                            if(withdraw!=0) {
                                cout << "Not enough change to withdraw!";
                                break;
                            }
                        }
                    }
                }
                case 5: {
                    cout << "Do you want to log out?" << "\n";
                    cout << "1. Yes       2. Return";
                    int eOpt;
                    cin >> eOpt;
                    while(eOpt<1||eOpt>2) {
                        cout << "Invalid selection. Please choose another option: ";
                        cin >> eOpt;
                    }
                    if(eOpt==1) {
                        cout << "Thank you for using my ATM! See you next time!" << "\n";
                        goto DISPLAY;
                    }
                    else if(eOpt==2) {
                        goto DOSOMETHINGWHENYOULOGIN;
                    }
                }
                default: break;
            }
        } while (true);
    }
    else {
        cout << "Card is deactivated, please try after 1 minute";
    }
    return 0;
}
