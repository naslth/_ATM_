#include"_ATM_.h"
void user::logIn()
{
    cin.ignore();
    cout << "Please fill your ID: ";
    getline(cin,id);
    cout << "Please fill your password: ";
    getline(cin,pass);
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
bool is_Account_In_File(user test,const string& path)
{
    ifstream fileIn;
    fileIn.open(path,ios_base::in);
    if(fileIn.is_open())
    {
        while (!fileIn.eof())
        {
            user temp;
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
bool is_Login_Successfully(user test)
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
    cout << "    5.   Change Password      " << "\n";
    cout << "    6.   Log out              " << "\n";
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
int checkBalance(user test, const string& path)
{
    test.value=readDataFromFileToMap(path);
    int balance = test.value[10000]*10000+test.value[20000]*20000+test.value[50000]*50000
                  +test.value[100000]*100000+test.value[200000]*200000+test.value[500000]*500000;
    return balance;
}
void checkTransHistory(const string& path)
{
    ifstream fileAccountHistoryIn;
    fileAccountHistoryIn.open(path,ios_base::in);
    if(fileAccountHistoryIn.is_open())
    {
        int i=0;
        while(fileAccountHistoryIn.eof())
        {
            i++;
            string temp;
            getline(fileAccountHistoryIn,temp);
            cout << temp << "\n";
        }
        if(i==0)
            cout << "Your transaction history is clear. Let make some transaction." << "\n";
    }
    else
        cout << "Can't open file." << "\n";
    fileAccountHistoryIn.close();
}
void changePass(string usernameNeedToChangePass, string newPass) {
    ifstream fileListAcccountIn;
    fileListAcccountIn.open("listAccount.txt",ios_base::in);
    ofstream tempOut;
    tempOut.open("temp.txt",ios_base::out);
    if(fileListAcccountIn.is_open()) {
        string line;
        while(getline(fileListAcccountIn,line)) {
            if(line!=usernameNeedToChangePass) {
                tempOut << line << "\n";
            }
            else getline(fileListAcccountIn,line);
        }
    }
    else cout << "Can't open file." << "\n";
    fileListAcccountIn.close();
    tempOut.close();
    remove("listAccount.txt");
    rename("temp.txt", "listAccount.txt");
    ofstream fileListAcccountOut;
    fileListAcccountOut.open("listAccount.txt",ios_base::app);
    if(fileListAcccountOut.is_open()){
        fileListAcccountOut << usernameNeedToChangePass << "\n";
        fileListAcccountOut << newPass << "\n";
    }
    else cout << "Can't open file." << "\n";
    fileListAcccountOut.close();
}
void tranfer(string accountTransferFrom, string accountTransferTo, int amount) {
    string accFromBalance=accountTransferFrom+"Balance";
    string accToBalance=accountTransferTo+"Balance";

}

