#include "../include/_ATM_.h"

User::User() {}

User::~User() {}

void User::setInfo(string _id,string _pass)
{
    this->id=_id;
    this->pass=_pass;
}


void User::setBalance(int _balance)
{
    this->balance=_balance;
}

string User::getID()
{
    return this->id;
}
string User::getPass()
{
    return this->pass;
}

bool User::is_Account_In_Datafile()
{
    ifstream fileIn;
    fileIn.open("data\\listAccount.txt",ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            string tempID,tempPass;
            fileIn >> tempID >> tempPass;
            if(tempID == this->id && tempPass == this->pass)
                return true;
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileIn.close();
    return false;
}


bool User::is_Login_Successfully(int x, int y)
{
    int check=5;
    do
    {
        gotoXY(x/2-7,y/2-6);
        cout << "Log in process:";
        gotoXY(x/2-15,y/2-4);
        cout << "Enter your ID: ";
        getline(cin,this->id);
        gotoXY(x/2-15,y/2-3);
        cout << "Enter your password: ";
        this->pass=maskingPass();
        cout << "\n\n";
        if(!is_Account_In_Datafile()||this->id=="")
        {
            check--;
            if (check == 0)
                return false;
            cout << "\t\t\tYour ID or password is incorrect. Please try again!" << "\n";
            if(check!=1)
                cout << "\t\t\tYou have " << check << " attempts left." << "\n";
            else
                cout << "\t\t\tYou have " << check << " attempt left." << "\n";
            Sleep(1500);
            system("cls");
        }
    }
    while(!is_Account_In_Datafile()||this->id=="");
    return true;
}



int User::checkBalance(const string& path)
{
    ifstream fileAccountIn;
    fileAccountIn.open(path,ios_base::in);
    if(fileAccountIn.is_open())
    {
        fileAccountIn >> this->balance;
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountIn.close();
    return this->balance;
}


void User::checkTransHistory(const string& path)
{
    ifstream fileAccountIn;
    fileAccountIn.open(path,ios_base::in);
    if(fileAccountIn.is_open())
    {
        fileAccountIn >> this->balance;
        while(!fileAccountIn.eof())
        {
            string temp;
            getline(fileAccountIn,temp);
            cout << temp << "\n";
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountIn.close();
}


void User::Deposit(const string& path, int moneyDeposit)
{
    this->balance=checkBalance(path)+moneyDeposit;
    int balance=this->balance;
    updateBalanceInFile(path,balance);
    ofstream fileOut;
    fileOut.open(path,ios_base::app);
    if(fileOut.is_open())
    {
        fileOut << "You have deposited " << moneyDeposit << " VND." << "\n";
    }
    else
        cout << "Can't open file.";
    fileOut.close();
}


void User::Withdraw(const string& path, int moneyWithdraw)
{
    const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};
    map<int,int> ATM_money;
    int tempWithdraw=moneyWithdraw;
    vector<int> atmCheckList;
// Đọc số dư tài khoản, đọc số tờ có trong cây ATM
    ATM_money=readDataFromFileToMap("data\\ATMinfo.txt");
    this->balance=checkBalance(path);
// dùng vòng for chạy từ mệnh giá lớn nhất đến mệnh giá nhỏ nhất
    for (int j = 5; j >= 0; j--)
    {
// tìm min của (số tiền rút/mệnh giá, số tờ hiên có trong cây ATM)
        int atmCheck = min((tempWithdraw / moneyArr[j]), ATM_money[moneyArr[j]]);
// số tiền rút -= min*mệnh giá
        tempWithdraw -= atmCheck * moneyArr[j];
// thêm số tờ rút ra vào vector để tí in ra
        atmCheckList.push_back(atmCheck);
// nếu số tiền cần rút = 0 => đã rút thành công
        if (tempWithdraw == 0)
        {
            if(atmCheckList.size()<6) // nếu rút không tới mệnh giá cuối cùng (10000 VND) thì thêm vào cho đủ 6 mệnh giá tiền
            {
                for(int j=atmCheckList.size(); j<6; j++)
                {
                    atmCheckList.push_back(0);
                }
            }
            reverse(atmCheckList.begin(),atmCheckList.end()); // đảo ngược về đúng thứ tự
// trừ số tiền rút khỏi cây ATM và tài khoản, cập nhật dữ liệu mới vào trong file
            for(int k=5; k>=0; k--)
            {
                ATM_money[moneyArr[k]]-=atmCheckList[k];
            }
            this->balance -= moneyWithdraw;
            int balance=this->balance;
            updateBalanceInFile(path,balance);
            writeDataFromMapToFile(ATM_money,"data\\ATMinfo.txt");
            ofstream fileOut;
            fileOut.open(path,ios_base::app);
            if(fileOut.is_open())
            {
                fileOut << "You have withdrawn " << moneyWithdraw << " VND." << "\n";
            }
            else
                cout << "Can't open file.";
            fileOut.close();
            cout << "Please wait a second..." << "\n";
            Sleep(1000);
            cout << "Successful withdrawal!" << "\n";
            for (int k = 5; k >= 0; k--)
            {
                if(atmCheckList[k]!=0)
                    cout << "The number of " << moneyArr[k] <<" VND bills is: " << atmCheckList[k] << endl;
            }
            cout << "Your current balance is: " << this->balance << " VND." << "\n";
            goBack();
            break; // out khỏi vòng for
        }
    }
// nếu só tiền cần rút sau khi chạy vòng for !=0 => không đủ tiền lẻ trong ATM để rút
    if(tempWithdraw!=0)
    {
        cout << "Not enough change to withdraw! Please try again!" << "\n";
        Sleep(1000);
    }
}


bool User::is_ID_In_ListAccount()
{
    ifstream fileIn;
    fileIn.open("data\\listAccount.txt",ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            string tempID,tempPass;
            fileIn >> tempID >> tempPass;
            if(tempID == this->id)
                return true;
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileIn.close();
    return false;

}


void tranfer(User accountTransfer,User accountReceive,int amount)
{
    string accountTransferInfo="data\\"+accountTransfer.id+"Info.txt";
    string accountReceiveInfo="data\\"+accountReceive.id+"Info.txt";
    int accountTransferBalance=accountTransfer.checkBalance(accountTransferInfo)-amount;
    int accountReceiveBalance=accountReceive.checkBalance(accountReceiveInfo)+amount;
    updateBalanceInFile(accountTransferInfo,accountTransferBalance);
    updateBalanceInFile(accountReceiveInfo,accountReceiveBalance);
    ofstream fileOut;
    fileOut.open(accountTransferInfo,ios_base::app);
    if(fileOut.is_open())
    {
        fileOut << "You have transferred " << amount << " VND to " << accountReceive.id << "\n";
    }
    else
        cout << "Can't open file.";
    fileOut.close();
    fileOut.open(accountReceiveInfo,ios_base::app);
    if(fileOut.is_open())
    {
        fileOut << "You have received " << amount << " VND from " << accountTransfer.id << "\n";
    }
    else
        cout << "Can't open file.";
    fileOut.close();
}


void User::changePass(string newPass)
{
    ifstream fileListAccountIn;
    fileListAccountIn.open("data\\listAccount.txt",ios_base::in);
    ofstream tempOut;
    tempOut.open("data\\temp.txt",ios_base::out);
    if(fileListAccountIn.is_open())
    {
        int i=0;
        while(!fileListAccountIn.eof())
        {
            string line;
            getline(fileListAccountIn,line);
            if(line!=this->id)
            {
                tempOut << line << "\n";
            }
            else
            {
                getline(fileListAccountIn,line);
                getline(fileListAccountIn,line);
            }
            i++;
        }
        if(i!=2)
        {
            tempOut << this->id << "\n";
            tempOut << newPass << "\n";
        }
        else
        {
            tempOut.seekp(0,ios_base::beg);
            tempOut << this->id << "\n";
            tempOut << newPass << "\n";
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileListAccountIn.close();
    tempOut.close();
    remove("data\\listAccount.txt");
    rename("data\\temp.txt", "data\\listAccount.txt");
}

