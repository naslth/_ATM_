#include "_ATM_.h"
void User::logIn()
{
    cout << "Enter your ID: ";
    getline(cin,this->id);
    cout << "Enter your password: ";
    this->pass=maskingPass();
}
bool is_ID_Valid(string id)
{
    int length=id.size();
    if(length<8||length>20)
        return false;
    for(int i=0; i<length; i++)
    {
        if((id[i]>='a'&&id[i]<='z')||(id[i]>='A'&&id[i]<='Z')||(id[i]>='0'&&id[i]<='9')||id[i]=='_'||id[i]=='.'||id[i]=='@')
            continue;
        else
            return false;
    }
    return true;
}
bool is_Pass_Valid(string pass)
{
    bool check1=false;
    bool check2=false;
    int length=pass.size();
    if(length<8||length>20)
        return false;
    for(int i=0; i<length; i++)
    {
        if(pass[i]==' ')
            return false;
    }
    for(int i=0; i<length; i++)
    {
        if(pass[i]>='A'&&pass[i]<='Z')
        {
            check1=true;
            break;
        }
    }
    for(int i=0; i<length; i++)
    {
        if(pass[i]>='0'&&pass[i]<='9')
        {
            check2=true;
            break;
        }
    }
    if(check1==true&&check2==true)
        return true;
    else
        return false;
}
bool is_Account_In_File(User test,const string& path)
{
    ifstream fileIn;
    fileIn.open(path,ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            User temp;
            fileIn >> temp.id;
            fileIn >> temp.pass;
            if(temp.id == test.id && temp.pass == test.pass)
                return true;
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileIn.close();
    return false;
}
bool is_Login_Successfully(User test)
{
    int check=5;
    while(!is_Account_In_File(test,"listAccount.txt"))
    {
        check--;
        if (check == 0)
            return false;
        cout << "Your ID or password is incorrect. Please try again!" << "\n";
        if(check!=1)
            cout << "You have " << check << " attempts left." << "\n";
        else
            cout << "You have " << check << " attempt left." << "\n";
        test.logIn();
    }
    return true;
}
void showMenu()
{
    cout << "-------------MENU-------------" << "\n";
    cout << "    1.   Transaction history  " << "\n";
    cout << "    2.   Check your balance   " << "\n";
    cout << "    3.   Deposit              " << "\n";
    cout << "    4.   Withdraw             " << "\n";
    cout << "    5.   Transfer             " << "\n";
    cout << "    6.   Change Password      " << "\n";
    cout << "    7.   Log out              " << "\n";
    cout << "------------------------------" << "\n" << "\n";
    cout << "    Please choose an option: ";
}
map<int,int> readDataFromFileToMap(const string& path)
{
    map<int,int> _map;
    _map[10000]=0;
    _map[20000]=0;
    _map[50000]=0;
    _map[100000]=0;
    _map[200000]=0;
    _map[500000]=0;
    map<int, int>::iterator i;
    ifstream fileIn;
    fileIn.open(path,ios_base::in);
    if(fileIn.is_open())
    {
        for(i=_map.begin(); i!=_map.end(); i++)
        {
            fileIn >> (i->second);
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileIn.close();
    return _map;
}
void writeDataFromMapToFile(map<int,int> _map, const string& path)
{
    map<int, int>::iterator i;
    ofstream fileOut;
    fileOut.open(path,ios_base::out);
    if(fileOut.is_open())
    {
        for (i = _map.begin(); i != _map.end(); i++)
        {
            fileOut << (i->second) << "\n";
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileOut.close();
}
int checkBalance(const string& path)
{
    int balance;
    ifstream fileAccountIn;
    fileAccountIn.open(path,ios_base::in);
    if(fileAccountIn.is_open())
    {
        fileAccountIn >> balance;
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountIn.close();
    return balance;
}
void checkTransHistory(const string& path)
{
    ifstream fileAccountIn;
    fileAccountIn.open(path,ios_base::in);
    if(fileAccountIn.is_open())
    {
        int i=0;
        int balance;
        fileAccountIn >> balance;
        cin.ignore();
        while(!fileAccountIn.eof())
        {
            i++;
            string temp;
            getline(fileAccountIn,temp);
            cout << temp << "\n";
        }
        if(i==0)
            cout << "Your transaction history is clear. Let make some transaction." << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountIn.close();
}
void Deposit(const string& _path, User test, int moneyDeposit)
{
    const char* path=_path.c_str();
    test.balance=checkBalance(path);
    test.balance+=moneyDeposit;
    ofstream tempOut;
    tempOut.open("temp.txt",ios_base::out);
    ifstream fileAccountIn;
    fileAccountIn.open(path,ios_base::in);
    if(tempOut.is_open())
    {
        tempOut << test.balance << "\n";
        int temp;
        fileAccountIn >> temp;
        string line;
        cin.ignore();
        while(!fileAccountIn.eof())
        {
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
    }
    else
        cout << "Can't open file.";
    fileAccountIn.close();
    tempOut.close();
    remove(path);
    rename("temp.txt",path);
    ofstream fileAccountOut;
    fileAccountOut.open(path,ios_base::app);
    if(fileAccountOut.is_open())
    {
        fileAccountOut << "You have deposited " << moneyDeposit << " VND." << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountOut.close();
}
void Withdraw(const string& _path, User test, int withdraw)
{
    const char* path=_path.c_str();
    const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};
    map<int,int> ATM_money;
    int tempWithdraw=withdraw;
    vector<int> atmCheckList;
// Đọc số dư tài khoản, đọc số tờ có trong cây ATM
    ATM_money=readDataFromFileToMap("ATMinfo.txt");
    test.balance=checkBalance(path);
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
            test.balance -= withdraw;
            ofstream tempOut;
            tempOut.open("temp.txt",ios_base::out);
            ifstream fileAccountIn;
            fileAccountIn.open(path,ios_base::in);
            if(tempOut.is_open())
            {
                tempOut << test.balance << "\n";
                int temp;
                fileAccountIn >> temp;
                string line;
                cin.ignore();
                while(!fileAccountIn.eof())
                {
                    getline(fileAccountIn,line);
                    tempOut << line << "\n";
                }
            }
            else
                cout << "Can't open file.";
            fileAccountIn.close();
            tempOut.close();
            remove(path);
            rename("temp.txt",path);
            writeDataFromMapToFile(ATM_money,"ATMinfo.txt");
            ofstream fileAccountOut;
            fileAccountOut.open(path,ios_base::app);
            if(fileAccountOut.is_open())
            {
                fileAccountOut << "You have withdrawn " << withdraw << " VND." << "\n";
            }
            else
                cout << "Can't open file." << "\n";
            fileAccountOut.close();
            cout << "Please wait a second..." << "\n";
            Sleep(1000);
            cout << "Successful withdrawal!" << "\n";
            for (int k = 5; k >= 0; k--)
            {
                if(atmCheckList[k]!=0)
                    cout << "The number of " << moneyArr[k] <<" VND bills is: " << atmCheckList[k] << endl;
            }
            cout << "Your current balance is: " << test.balance << " VND." << "\n";
            char temp;
            cout << "Enter 'b' to go back: ";
            do
            {
                cin >> temp;
            }
            while(temp!='b');
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
bool is_ID_In_ListAccount(string ID)
{
    ifstream fileIn;
    fileIn.open("listAccount.txt",ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            User temp;
            fileIn >> temp.id;
            fileIn >> temp.pass;
            if(temp.id == ID)
                return true;
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileIn.close();
    return false;

}
void tranfer(string accountTransfer, string accountReceive,int accountTransferBalance, int amount)
{
    const char* accountTransferInfo=(accountTransfer+"Info.txt").c_str();
    const char* accountReceiveInfo=(accountReceive+"Info.txt").c_str();
    int accountReceiveBalance=checkBalance(accountReceiveInfo);
    accountTransferBalance-=amount;
    accountReceiveBalance+=amount;
    ofstream tempOut;
    tempOut.open("temp.txt",ios_base::out);
    ifstream fileAccountIn;
    fileAccountIn.open(accountTransferInfo,ios_base::in);
    if(tempOut.is_open())
    {
        tempOut << accountTransferBalance << "\n";
        int temp;
        fileAccountIn >> temp;
        string line;
        while(!fileAccountIn.eof())
        {
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
    }
    else
        cout << "Can't open file.";
    fileAccountIn.close();
    tempOut.close();
    remove(accountTransferInfo);
    rename("temp.txt",accountTransferInfo);
    tempOut.open("temp.txt",ios_base::out);
    fileAccountIn.open(accountReceiveInfo,ios_base::in);
    if(tempOut.is_open())
    {
        tempOut << accountReceiveBalance << "\n";
        int temp;
        fileAccountIn >> temp;
        string line;
        while(!fileAccountIn.eof())
        {
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
    }
    else
        cout << "Can't open file.";
    fileAccountIn.close();
    tempOut.close();
    remove(accountReceiveInfo);
    rename("temp.txt",accountReceiveInfo);
    ofstream fileAccountOut;
    fileAccountOut.open(accountTransferInfo,ios_base::app);
    if(fileAccountOut.is_open())
    {
        fileAccountOut << "You have transferred " << amount << " VND to " << accountReceive << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountOut.close();
    fileAccountOut.open(accountReceiveInfo,ios_base::app);
    if(fileAccountOut.is_open())
    {
        fileAccountOut << "You have received " << amount << " VND from " << accountTransfer << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountOut.close();
}
void changePass(string usernameNeedToChangePass, string newPass)
{
    ifstream fileListAcccountIn;
    fileListAcccountIn.open("listAccount.txt",ios_base::in);
    ofstream tempOut;
    tempOut.open("temp.txt",ios_base::out);
    if(fileListAcccountIn.is_open())
    {
        string line;
        while(!fileListAcccountIn.eof())
        {
            getline(fileListAcccountIn,line);
            if(line!=usernameNeedToChangePass)
            {
                tempOut << line << "\n";
            }
            else
                getline(fileListAcccountIn,line);
        }
    }
    else
        cout << "Can't open file." << "\n";
    fileListAcccountIn.close();
    tempOut.close();
    remove("listAccount.txt");
    rename("temp.txt", "listAccount.txt");
    ofstream fileListAccountOut;
    fileListAccountOut.open("listAccount.txt",ios_base::app);
    if(fileListAccountOut.is_open())
    {
        fileListAccountOut << usernameNeedToChangePass << "\n";
        fileListAccountOut << newPass << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileListAccountOut.close();
}

