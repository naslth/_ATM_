#include"_ATM_.h"
int main()
{
    const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};
    bool exit = false;
while(!exit)
{
    cout << "   THIS IS MY ATM!!    " << "\n";
    cout << "Do you have an account?" << "\n";
    cout << "1. Yes, I have an account" << "\n";
    cout << "2. No, not yet" << "\n";
    cout << "3. Exit" << "\n";
    cout << "Choose your option: ";
    int answer;
    cin >> answer;
    while(answer!=1&&answer!=2&&answer!=3)
    {
        cout << "Your option is invalid. Please choose another option!" << "\n";
        cout << "Choose your option: ";
        cin >> answer;
    }
    if(answer==1)
    {
        cout << "Please wait a second to go to log in process..." << "\n";
        Sleep(2000);
    }
    else if(answer==2)
    {
        cout << "Please wait a second to go to sign up process..." << "\n";
        Sleep(2000);
        system("cls");
        string accountBalance="";
        string accountHistory="";
        user temp("0","0");
        fstream fileListAccount;
        fileListAccount.open("listAccount.txt",ios_base::in | ios_base::out | ios_base::app);
        if(fileListAccount.is_open())
        {
            cout << "Please register here:" << "\n";
            cout << "Your ID is: ";
            cin >> temp.id;
            user temp2("0","0");
            bool check=true;
            while(true)
            {
                while (!fileListAccount.eof())
                {
                    fileListAccount >> temp2.id;
                    fileListAccount >> temp2.pass;
                    if(temp2.id == temp.id)
                    {
                        check=false;
                    }
                }
                if(check==false)
                {
                    check=true;
                    cout << "Your ID is already exist. Please try again!" << "\n";
                    cout << "Your ID is: ";
                    cin >> temp.id;
                    fileListAccount.clear();
                    fileListAccount.seekg(0, ios_base::beg);
                }
                else if(check==true)
                {
                    fileListAccount.seekp(0, ios_base::end);
                    break;
                }
            }
            fileListAccount.clear();
            fileListAccount << temp.id << "\n";
            cout << "Your ID is valid." << "\n";
            cout << "Your password is: ";
            cin >> temp.pass;
            cout << "Confirm your password: ";
            string passcf;
            cin >> passcf;
            while(passcf!=temp.pass)
            {
                cout << "Password confirmation does not match. Try again!" << "\n";
                cout << "Your password is: ";
                cin >> temp.pass;
                cout << "Confirm your password: ";
                cin >> passcf;
            }
            fileListAccount << temp.pass << "\n";
            accountBalance=temp.id + "Balance";
            accountHistory=temp.id + "History";
        }
        else cout << "Can't open file.";
        fileListAccount.close();
        ofstream fileAccountBalance;
        fileAccountBalance.open(accountBalance,ios_base::out);
        if(fileAccountBalance.is_open())
        {
            map<int,int>::iterator i;
            for (i = (temp.value).begin(); i != (temp.value).end(); i++)
            {
                fileAccountBalance << (i->second) << "\n";
            }
        }
        else cout << "Can't open file.";
        fileAccountBalance.close();
        ofstream fileAccountHistory;
        fileAccountHistory.open(accountHistory,ios_base::out);
        if(!fileAccountHistory.is_open()) cout << "Can't open file.";
        fileAccountHistory.close();
        cout << "Please wait a second..." << "\n";
        Sleep(1000);
        cout << "Sign up success. Please wait a second and log in to your account..." << "\n";
        Sleep(1000);
        system("cls");
        continue;
    }
    else if(answer==3) {
        exit=true;
        continue;
    }
    system("cls");
    user test("0","0");
    test.logIn();
    if(logInsuccessfully(test))
    {
        map<int,int> ATM_money;
        map<int, int>::iterator i;
        for(int j=0; j<6; j++)
        {
            ATM_money[moneyArr[j]]=0;
        }
        cout << "Please wait a second..." << "\n";
        Sleep(1000);
        cout << "Log in successfully!" << "\n";
        const string accountBalance=test.id+"Balance";
        const string accountHistory=test.id+"History";
        int menuOpt;
        bool logout=false;
        while(!logout)
        {
            system("cls");
            showMenu();
            cin >> menuOpt;
            while(menuOpt<1||menuOpt>5)
            {
                cout << "Invalid selection. Please choose another option: ";
                cin >> menuOpt;
            }
            switch(menuOpt)
            {
            case 1:
            {
                cout << "Please wait a second..." << "\n";
                Sleep(1000);
                cout << "This is your transaction history: " << "\n";
                checkTransHistory(accountHistory);
                char temp;
                cout << "Enter 'b' to go back to menu: ";
                cin >> temp;
                while(temp!='b') cin >> temp;
                break;
            }
            case 2:
            {
                int balance;
                balance=checkBalance(test,accountBalance);
                cout << "Please wait a second..." << "\n";
                Sleep(1000);
                cout << "Your balance is: " << balance << " VND." << "\n";
                char temp;
                cout << "Enter 'b' to go back to menu: ";
                cin >> temp;
                while(temp!='b')
                    cin >> temp;
                break;
            }
            case 3:
            {
                int dOpt;
                cout << "Please wait a second..." << "\n";
                Sleep(1000);
                cout << "Choose an option: " << "\n";
                cout << "1. Deposit         2. Exit" << "\n";
                cout << "Choose your option: ";
                cin >> dOpt;
                while(dOpt!=1&&dOpt!=2)
                {
                    cout << "Invalid selection. Please choose another option: ";
                    cin >> dOpt;
                }
                if(dOpt==1)
                {
                    int denominations;
                    int bills;
                    bool checkDenominations=false;
                    cout << "Enter the denominations: ";
                    do
                    {
                        cin >> denominations;
                        for (i = (test.value).begin(); i != (test.value).end(); i++)
                        {
                            if((i->first)==denominations) checkDenominations=true;
                        }
                        if(!checkDenominations) cout << "The face value must be 10000, 20000, 50000, 100000, 200000, 500000 (VND)." << "\n";
                    } while(!checkDenominations);
                    cout << "Enter the bills: ";
                    cin >> bills;
                    test.value=readDataFromFileToMap(accountBalance);
                    for (i = (test.value).begin(); i != (test.value).end(); i++)
                    {
                        if((i->first)==denominations)
                        {
                            (i->second)+=bills;
                        }
                    }
                    writeDataFromMapToFile((test.value),accountBalance);
                    ofstream fileAccountHistoryOut;
                    fileAccountHistoryOut.open(accountHistory,ios_base::app);
                    if(fileAccountHistoryOut.is_open())
                    {
                        fileAccountHistoryOut << "You have deposited " << bills*denominations << " VND." << "\n";
                    }
                    else cout << "Can't open file." << "\n";
                    fileAccountHistoryOut.close();
                    int currentBalance=checkBalance(test,accountBalance);
                    cout << "Please wait a second..." << "\n";
                    Sleep(1000);
                    cout << "Deposit successfully. Your current balance is: " << currentBalance << " VND" << "\n";
                    fstream fileATM;
                    fileATM.open("ATMinfo.txt",ios_base::in | ios_base::out);
                    if(fileATM.is_open())
                    {
                        fileATM.seekg(0, ios_base::beg);
                        for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                        {
                            fileATM >> (i->second);
                        }
                        for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                        {
                            if((i->first)==denominations)
                                (i->second)+=bills;
                        }
                        fileATM.clear();
                        fileATM.seekp(0, ios_base::beg);
                        for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                        {
                            fileATM << i->second << "\n";
                        }
                        fileATM.clear();
                    }
                    else cout << "Can't open file.";
                    fileATM.close();
                    char temp;
                    cout << "Enter 'b' to go back to menu: ";
                    cin >> temp;
                    while(temp!='b')
                    {
                        cin >> temp;
                    }
                    break;
                }
                if(dOpt==2) break;
            }
            case 4:
            {
                int wOpt;
                cout << "Please wait a second..." << "\n";
                Sleep(1000);
                cout << "Choose an option: " << "\n";
                cout << "1. Withdraw         2. Exit" << "\n";
                cout << "Choose your option: ";
                cin >> wOpt;
                while(wOpt!=1&&wOpt!=2)
                {
                    cout << "Invalid selection. Please choose another option: ";
                    cin >> wOpt;
                }
                if(wOpt==1)
                {
                    ATM_money=readDataFromFileToMap("ATMinfo.txt");
                    test.value=readDataFromFileToMap(accountBalance);
                    int minwithdraw;
                    for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                    {
                        if((i->second)!=0)
                        {
                            minwithdraw=(i->first);
                            break;
                        }
                    }
                    int balance,withdraw;
                    balance=checkBalance(test,accountBalance);
                    cout << "Your balance is: " << balance << " VND." << "\n";
                    cout << "How much do you want to withdraw? ";
                    cin >> withdraw;
                    if(withdraw<minwithdraw)
                    {
                        cout << "The smallest amount that can be withdrawn is: " << minwithdraw << " . Please try again!" << "\n";
                        Sleep(1000);
                        break;
                    }
                    else if(withdraw%minwithdraw!=0)
                    {
                        cout << "Not enough change to withdraw! The withdrawal amount must be a multiple of " << minwithdraw << " . Please try again!" << "\n";
                        Sleep(1000);
                        break;
                    }
                    else
                    {
                        if((withdraw%500000==0) && (ATM_money[500000]>(withdraw/500000)))
                        {
                            ATM_money[500000]-=(withdraw/500000);
                            test.value[500000]-=(withdraw/500000);
                            writeDataFromMapToFile((test.value),accountBalance);
                            writeDataFromMapToFile(ATM_money,"ATMinfo.txt");
                            ofstream fileAccountHistoryOut;
                            fileAccountHistoryOut.open(accountHistory,ios_base::app);
                            if(fileAccountHistoryOut.is_open())
                            {
                                fileAccountHistoryOut << "You have withdrawn " << withdraw << " VND." << "\n";
                            }
                            else cout << "Can't open file." << "\n";
                            fileAccountHistoryOut.close();
                            cout << "Please wait a second..." << "\n";
                            Sleep(1000);
                            cout << "Successful withdrawal!" << "\n";
                            cout << "The number of 500000 VND bills is: " << withdraw/500000 << "\n";
                            int currentBalance=checkBalance(test,accountBalance);
                            cout << "Your current balance is: " << currentBalance << " VND." << "\n";
                            char temp;
                            cout << "Enter 'b' to go back to menu: ";
                            cin >> temp;
                            while(temp!='b')
                                cin >> temp;
                            break;
                        }
                        else
                        {
                            int tempWithdraw=withdraw;
                            vector<int> atmCheckList;
                            for (int j = 5; j >= 0; j--)
                            {
                                int atmCheck = min((tempWithdraw / moneyArr[j]), ATM_money[moneyArr[j]]);
                                tempWithdraw -= atmCheck * moneyArr[j];
                                atmCheckList.push_back(atmCheck);
                                if (tempWithdraw == 0)
                                {
                                    if(atmCheckList.size()<6)
                                    {
                                        for(int j=atmCheckList.size(); j<6; j++)
                                        {
                                            atmCheckList.push_back(0);
                                        }
                                    }
                                    reverse(atmCheckList.begin(),atmCheckList.end());
                                    for(int k=5; k>=0; k--)
                                    {
                                        ATM_money[moneyArr[k]]-=atmCheckList[k];
                                        test.value[moneyArr[k]]-=atmCheckList[k];
                                    }
                                    writeDataFromMapToFile((test.value),accountBalance);
                                    writeDataFromMapToFile(ATM_money,"ATMinfo.txt");
                                    ofstream fileAccountHistoryOut;
                                    fileAccountHistoryOut.open(accountHistory,ios_base::app);
                                    if(fileAccountHistoryOut.is_open())
                                    {
                                        fileAccountHistoryOut << "You have withdrawn " << withdraw << " VND." << "\n";
                                    }
                                    else cout << "Can't open file." << "\n";
                                    fileAccountHistoryOut.close();
                                    cout << "Please wait a second..." << "\n";
                                    Sleep(1000);
                                    cout << "Successful withdrawal!" << "\n";
                                    for (int k = 5; k >= 0; k--)
                                    {
                                        if(atmCheckList[k]!=0) cout << "The number of " << moneyArr[k] <<" VND bills is: " << atmCheckList[k] << endl;
                                    }
                                    int currentBalance=checkBalance(test,accountBalance);
                                    cout << "Your current balance is: " << currentBalance << " VND." << "\n";
                                    char temp;
                                    cout << "Enter 'b' to go back to menu: ";
                                    cin >> temp;
                                    while(temp!='b')
                                        cin >> temp;
                                    break;
                                }
                            }
                            if(withdraw!=0)
                            {
                                cout << "Not enough change to withdraw! Please try again!" << "\n";
                                Sleep(1000);
                                break;
                            }
                        }
                    }
                }
                if(wOpt==2) break;
            }
            case 5:
            {
                cout << "Do you want to log out?" << "\n";
                cout << "1. Yes       2. Return" << "\n";
                cout << "Choose your option: ";
                int eOpt;
                cin >> eOpt;
                while(eOpt<1||eOpt>2)
                {
                    cout << "Invalid selection. Please choose another option: ";
                    cin >> eOpt;
                }
                if(eOpt==1)
                {
                    cout << "Please wait a second..." << "\n";
                    Sleep(1000);
                    cout << "Thank you for using my ATM! See you next time!" << "\n";
                    Sleep(2000);
                    system("cls");
                    logout=true;
                    break;
                }
                else if(eOpt==2) break;
            }
            default:
                break;
            }
        }
    }
    else
    {
        cout << "Card is deactivated, please try after 1 minute.";
        exit=true;
        continue;
    }
}
    return 0;
}
