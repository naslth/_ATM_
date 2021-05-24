#include "../include/_ATM_.h"

User::User() {}

User::~User() {}

void User::setInfo(std::string _id,std::string _pass)
{
    this->id=_id;
    this->pass=_pass;
}


void User::setBalance(int _balance)
{
    this->balance=_balance;
}

std::string User::getID()
{
    return this->id;
}
std::string User::getPass()
{
    return this->pass;
}

bool User::is_Account_In_Datafile()
{
    std::ifstream fileIn;
    fileIn.open("data\\listAccount.txt",std::ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            std::string tempID,tempPass;
            fileIn >> tempID >> tempPass;
            if(tempID == this->id && tempPass == this->pass)
                return true;
        }
    }
    else
        std::cout << "Can't open file." << "\n";
    fileIn.close();
    return false;
}


bool User::is_Login_Successfully(int x, int y)
{
    int check=5;
    do
    {
        gotoXY(x/2-7,y/2-8);
        std::cout << " /    _  / ";
        gotoXY(x/2-7,y/2-7);
        std::cout << "(__()(/ //)";
        gotoXY(x/2-7,y/2-6);
        std::cout << "    _/     ";
        gotoXY(x/2-15,y/2-4);
        std::cout << "Enter your ID: ";
        getline(std::cin,this->id);
        gotoXY(x/2-15,y/2-3);
        std::cout << "Enter your password: ";
        this->pass=maskingPass();
        std::cout << "\n\n";
        if(!is_Account_In_Datafile()||this->id=="")
        {
            check--;
            if (check == 0)
                return false;
            std::cout << "\t\t\tYour ID or password is incorrect. Please try again!" << "\n";
            if(check!=1)
                std::cout << "\t\t\tYou have " << check << " attempts left." << "\n";
            else
                std::cout << "\t\t\tYou have " << check << " attempt left." << "\n";
            Sleep(1500);
            system("cls");
        }
    }
    while(!is_Account_In_Datafile()||this->id=="");
    return true;
}



int User::checkBalance(const std::string& path)
{
    std::ifstream fileAccountIn;
    fileAccountIn.open(path,std::ios_base::in);
    if(fileAccountIn.is_open())
    {
        fileAccountIn >> this->balance;
    }
    else
        std::cout << "Can't open file." << "\n";
    fileAccountIn.close();
    return this->balance;
}


void User::checkTransHistory(const std::string& path)
{
    std::ifstream fileAccountIn;
    fileAccountIn.open(path,std::ios_base::in);
    if(fileAccountIn.is_open())
    {
        int i=0;
        fileAccountIn >> this->balance;
        while(!fileAccountIn.eof())
        {
            std::string temp;
            getline(fileAccountIn,temp);
            std::cout << "\t" << temp << "\n";
            i++;
        }
        if(i==2) std::cout << "Transaction history is clear. Let make some transaction. \n\n";
    }
    else
        std::cout << "Can't open file." << "\n";
    fileAccountIn.close();
}


void User::Deposit(const std::string& path, int moneyDeposit)
{
    this->balance=checkBalance(path)+moneyDeposit;
    int balance=this->balance;
    updateBalanceInFile(path,balance);
    std::ofstream fileOut;
    fileOut.open(path,std::ios_base::app);
    std::string currentTime=getCurrentTime();
    if(fileOut.is_open())
    {
        fileOut << "You have deposited " << moneyDeposit << " VND in " << currentTime;
    }
    else
        std::cout << "Can't open file.";
    fileOut.close();
}


void User::Withdraw(const std::string& path, int moneyWithdraw)
{
    const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};
    std::map<int,int> ATM_money;
    int tempWithdraw=moneyWithdraw;
    std::vector<int> atmCheckList;
// Đọc số dư tài khoản, đọc số tờ có trong cây ATM
    ATM_money=readDataFromFileToMap("data\\ATMinfo.txt");
    this->balance=checkBalance(path);
// dùng vòng for chạy từ mệnh giá lớn nhất đến mệnh giá nhỏ nhất
    for (int j = 5; j >= 0; j--)
    {
// tìm min của (số tiền rút/mệnh giá, số tờ hiên có trong cây ATM)
        int atmCheck = std::min((tempWithdraw / moneyArr[j]), ATM_money[moneyArr[j]]);
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
            std::string currentTime=getCurrentTime();
            std::ofstream fileOut;
            fileOut.open(path,std::ios_base::app);
            if(fileOut.is_open())
            {
                fileOut << "You have withdrawn " << moneyWithdraw << " VND in " << currentTime;
            }
            else
                std::cout << "Can't open file.";
            fileOut.close();
            std::cout << "Please wait a second..." << "\n\n";
            Sleep(700);
            for (int k = 5; k >= 0; k--)
            {
                if(atmCheckList[k]!=0)
                    std::cout << "The number of " << moneyArr[k] <<" VND bills is: " << atmCheckList[k] << "\n";
            }
            std::cout << "Successful withdrawal!.Your current balance is: " << this->balance << " VND." << "\n\n";
            goBack();
            break; // out khỏi vòng for
        }
    }
// nếu só tiền cần rút sau khi chạy vòng for !=0 => không đủ tiền lẻ trong ATM để rút
    if(tempWithdraw!=0)
    {
        std::cout << "Not enough change to withdraw! Please try again!" << "\n";
        Sleep(1000);
    }
}


bool User::is_ID_In_ListAccount()
{
    std::ifstream fileIn;
    fileIn.open("data\\listAccount.txt",std::ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            std::string tempID,tempPass;
            fileIn >> tempID >> tempPass;
            if(tempID == this->id)
                return true;
        }
    }
    else
        std::cout << "Can't open file." << "\n";
    fileIn.close();
    return false;

}


void tranfer(User accountTransfer,User accountReceive,int amount)
{
    std::string accountTransferInfo="data\\"+accountTransfer.id+"Info.txt";
    std::string accountReceiveInfo="data\\"+accountReceive.id+"Info.txt";
    int accountTransferBalance=accountTransfer.checkBalance(accountTransferInfo)-amount;
    int accountReceiveBalance=accountReceive.checkBalance(accountReceiveInfo)+amount;
    updateBalanceInFile(accountTransferInfo,accountTransferBalance);
    updateBalanceInFile(accountReceiveInfo,accountReceiveBalance);
    std::string currentTime=getCurrentTime();
    std::ofstream fileOut;
    fileOut.open(accountTransferInfo,std::ios_base::app);
    if(fileOut.is_open())
    {
        fileOut << "You have transferred " << amount << " VND to " << accountReceive.id << " in " << currentTime;
    }
    else
       std:: cout << "Can't open file.";
    fileOut.close();
    fileOut.open(accountReceiveInfo,std::ios_base::app);
    if(fileOut.is_open())
    {
        fileOut << "You have received " << amount << " VND from " << accountTransfer.id << " in " << currentTime;
    }
    else
        std::cout << "Can't open file.";
    fileOut.close();
}


void User::changePass(std::string newPass)
{
    std::ifstream fileListAccountIn;
    fileListAccountIn.open("data\\listAccount.txt",std::ios_base::in);
    std::ofstream tempOut;
    tempOut.open("data\\temp.txt",std::ios_base::out);
    if(fileListAccountIn.is_open())
    {
        int isOnlyOne=0;
        while(!fileListAccountIn.eof())
        {
            std::string line;
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
            isOnlyOne++;
        }
// kiểm tra xem listAccount có phải chỉ có 1 tài khoản không
        if(isOnlyOne!=2)
        {
            tempOut << this->id << "\n";
            tempOut << newPass << "\n";
        }
        else
        {
            tempOut.seekp(0,std::ios_base::beg);
            tempOut << this->id << "\n";
            tempOut << newPass << "\n";
        }
    }
    else
        std::cout << "Can't open file." << "\n";
    fileListAccountIn.close();
    tempOut.close();
    remove("data\\listAccount.txt");
    rename("data\\temp.txt", "data\\listAccount.txt");
}

