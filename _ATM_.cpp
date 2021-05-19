#include "_ATM_.h"

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
        Sleep(1500);
        system("cls");
        if(check!=1)
            cout << "You have " << check << " attempts left." << "\n";
        else
            cout << "You have " << check << " attempt left." << "\n";
        cout << "Enter your ID: ";
        getline(cin,test.id);
        cout << "Enter your password: ";
        test.pass=maskingPass();
        cout << "\n";
    }
    return true;
}


int showDisplayAndChooseOpt(int x, int y)
{
    int Color[] = {7,7,7,7};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    gotoXY(x/2-17,y/2-11);
    setColor(Color[0]);
    cout << "This is my ATM - BANKING SYSTEM !!!";
    int a = y/2-9;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            gotoXY(x/2-15 + j, a);
            cout << "-";
        }
        a++;
        if (i != 3)
        {
            for(int j=a; j<a+3; j++)
            {
                gotoXY(x/2-15, j);
                cout << "|";
                gotoXY(x/2-15 + 29, j);
                cout << "|";
            }
        }
        a=a+3;
    }
    while(true)
    {

        gotoXY(x/2-14,y/2-7);
        setColor(Color[1]);
        cout << " 1.  Sign up for an account";

        gotoXY(x/2-14,y/2-3);
        setColor(Color[2]);
        cout << " 2.  Log in to account";

        gotoXY(x/2-14,y/2+1);
        setColor(Color[3]);
        cout << " 3.  Exit";

        key=_getch();
        if(key==72&&(counter>=2&&counter<=3))
        {
            counter--;
        }
        if(key==80&&(counter>=1&&counter<=2))
        {
            counter++;
        }
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }
        for(int i=1; i<=3; i++)
        {
            if(counter==i)
            {
                Color[i]=12;
            }
            else
                Color[i]=7;
        }
    }
    setColor(7);
    ShowCur(true);
    return answer;
}


int showMenuAndChooseOpt(int x, int y)
{
    int Color[] = {7,7,7,7,7,7,7,7};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    gotoXY(x/2-15,y/2-12);
    setColor(Color[0]);
    cout << "-----------------MENU-----------------";
    int a = y/2-11;
    for (int i = 0; i < 8; i++)
    {
        if(i!=0)
        {
            for (int j = 0; j < 38; j++)
            {
                gotoXY(x/2-15 + j, a);
                cout << "-";
            }
            a++;
        }
        if (i != 7)
        {
            gotoXY(x/2-15, a);
            cout << "|";
            gotoXY(x/2-15 + 37, a);
            cout << "|";
            gotoXY(x/2-15, a+1);
            cout << "|";
            gotoXY(x/2-15 + 37, a+1);
            cout << "|";
        }
        a=a+2;
    }
    while(true)
    {

        gotoXY(x/2-14,y/2-10);
        setColor(Color[1]);
        cout << "    1.   Transaction history";

        gotoXY(x/2-14,y/2-7);
        setColor(Color[2]);
        cout << "    2.   Check your balance";

        gotoXY(x/2-14,y/2-4);
        setColor(Color[3]);
        cout << "    3.   Deposit";

        gotoXY(x/2-14,y/2-1);
        setColor(Color[4]);
        cout << "    4.   Withdraw";

        gotoXY(x/2-14,y/2+2);
        setColor(Color[5]);
        cout << "    5.   Transfer";

        gotoXY(x/2-14,y/2+5);
        setColor(Color[6]);
        cout << "    6.   Change Password";

        gotoXY(x/2-14,y/2+8);
        setColor(Color[7]);
        cout << "    7.   Log out";

        key=_getch();
        if(key==72&&(counter>=2&&counter<=7))
        {
            counter--;
        }
        if(key==80&&(counter>=1&&counter<=6))
        {
            counter++;
        }
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }
        for(int i=1; i<=7; i++)
        {
            if(counter==i)
            {
                Color[i]=12;
            }
            else
                Color[i]=7;
        }
    }
    setColor(7);
    ShowCur(true);
    return answer;
}


int showOptAndChoose(int x,int y,int caseOpt)
{
    int Color[] = {7,7};
    int counter=1;
    int answer;
    char key;
    ShowCur(false);
    gotoXY(x/2-14,y/2-11);
    setColor(Color[0]);
    cout << "Please choose an option";
    int a = y/2-9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 35; j++)
        {
            gotoXY(x/2-15 + j, a);
            cout << "-";
        }
        a++;
        if (i != 2)
        {
            for(int j=a; j<a+3; j++)
            {
                gotoXY(x/2-15, j);
                cout << "|";
                gotoXY(x/2-15 + 34, j);
                cout << "|";
            }
        }
        a=a+3;
    }
    while(true)
    {

        gotoXY(x/2-14,y/2-7);
        setColor(Color[1]);
        if(caseOpt==1)
            cout << " 1.  Check transaction history";
        else if(caseOpt==2)
            cout << " 1.   Check balance";
        else if(caseOpt==3)
            cout << " 1.   Deposit";
        else if(caseOpt==4)
            cout << " 1.   Withdraw";
        else if(caseOpt==5)
            cout << " 1.   Tranfer";
        else if(caseOpt==6)
            cout << " 1.   Change password";
        else if(caseOpt==7)
            cout << " 1.   Log out";

        gotoXY(x/2-14,y/2-3);
        setColor(Color[2]);
        cout << " 2.   Return";

        key=_getch();
        if(key==72&&(counter==2))
        {
            counter--;
        }
        if(key==80&&(counter==1))
        {
            counter++;
        }
        if(key=='\r')
        {
            answer=counter;
            system("cls");
            break;
        }
        for(int i=1; i<=2; i++)
        {
            if(counter==i)
            {
                Color[i]=12;
            }
            else
                Color[i]=7;
        }
    }
    setColor(7);
    ShowCur(true);
    return answer;
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
        while(!fileAccountIn.eof())
        {
            i++;
            string temp;
            getline(fileAccountIn,temp);
            cout << temp << "\n";
        }
        if(i==0)
            cout << "Your transaction history is clear. Let make some transaction." << "\n";
        else
            cout << "This is your transaction history: " << "\n";
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
        fileAccountIn.seekg(1,ios_base::cur);
        while(!fileAccountIn.eof())
        {
            string line;
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
        tempOut.seekp(-1,ios_base::cur);
        tempOut << "You have deposited " << moneyDeposit << " VND." << "\n";
    }
    else
        cout << "Can't open file.";
    fileAccountIn.close();
    tempOut.close();
    remove(path);
    rename("temp.txt",path);
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
                fileAccountIn.seekg(1,ios_base::cur);
                while(!fileAccountIn.eof())
                {
                    string line;
                    getline(fileAccountIn,line);
                    tempOut << line << "\n";
                }
                tempOut.seekp(-1,ios_base::cur);
                tempOut << "You have withdrawn " << withdraw << " VND." << "\n";
            }
            else
                cout << "Can't open file.";
            fileAccountIn.close();
            tempOut.close();
            remove(path);
            rename("temp.txt",path);
            writeDataFromMapToFile(ATM_money,"ATMinfo.txt");
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
            cout << "Press 'b' to go back";
            do
            {
                temp=_getch();
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
        fileAccountIn.seekg(1,ios_base::cur);
        string line;
        while(!fileAccountIn.eof())
        {
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
        tempOut.seekp(-1,ios_base::cur);
        tempOut << "You have transferred " << amount << " VND to " << accountReceive << "\n";
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
        fileAccountIn.seekg(1,ios_base::cur);
        string line;
        while(!fileAccountIn.eof())
        {
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
        tempOut.seekp(-1,ios_base::cur);
        tempOut << "You have received " << amount << " VND from " << accountTransfer << "\n";
    }
    else
        cout << "Can't open file.";
    fileAccountIn.close();
    tempOut.close();
    remove(accountReceiveInfo);
    rename("temp.txt",accountReceiveInfo);
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
        tempOut.seekp(-1,ios_base::cur);
        tempOut << usernameNeedToChangePass << "\n";
        tempOut << newPass << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileListAcccountIn.close();
    tempOut.close();
    remove("listAccount.txt");
    rename("temp.txt", "listAccount.txt");
}

