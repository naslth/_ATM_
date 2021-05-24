#include "../include/_ATM_.h"


void signUp(std::string tempID, std::string tempPass)
{
    bool is_List_Account_Clear=false;;
    std::ifstream fileListAccountIn;
// Kiểm tra listAccount có rỗng không
    fileListAccountIn.open("data\\listAccount.txt",std::ios_base::in);
    if(fileListAccountIn.is_open())
    {
        fileListAccountIn.seekg(0, std::ios_base::end);
        if (fileListAccountIn.tellg() == 0)
        {
            is_List_Account_Clear=true;
        }
    }
    else
        std::cout << "Can't open file.";
    fileListAccountIn.close();
    std::ofstream fileListAccountOut;
    fileListAccountOut.open("data\\listAccount.txt",std::ios_base::app);
    if(fileListAccountOut.is_open())
    {
        if(is_List_Account_Clear)
        {
            fileListAccountOut << tempID << "\n";
            fileListAccountOut << tempPass << "\n";
        }
        else
        {
            fileListAccountOut << "\n" << tempID << "\n";
            fileListAccountOut << tempPass << "\n";
        }
    }
    else
        std::cout << "Can't open file.";
    fileListAccountOut.close();
// Tạo file chứa thông tin của tài khoản vừa đăng ký và ghi vào số dư hiện tại (0 VND)
    std::string accountInfo="data\\" + tempID + "Info.txt";
    std::ofstream fileAccountInfo;
    fileAccountInfo.open(accountInfo,std::ios_base::out);
    if(!fileAccountInfo.is_open())
        std::cout << "Can't open file.";
    else
        fileAccountInfo << "0" << "\n";
    fileAccountInfo.close();
    std::cout << "Please wait a second..." << "\n\n";
    Sleep(700);
    std::cout << "Sign up successfully." << "\n";
    std::cout << "Please wait a second and log in to your account..." << "\n";
    Sleep(1500);
    system("cls");
}


bool is_ID_Valid(std::string id)
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


bool is_Pass_Valid(std::string pass)
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


std::string maskingPass()
{
    char temp;
    std::string maskedPass="";
    while((temp=_getch()) != '\r')
    {
        if(temp!='\b')
        {
            std::cout << "*";
            maskedPass+=temp;
        }
        else if(maskedPass.size()!=0)
        {
            std::cout << "\b" << " " << "\b";
            maskedPass.pop_back();
        }
    }
    return maskedPass;
}



std::map<int,int> readDataFromFileToMap(const std::string& path)
{
    std::map<int,int> _map;
    _map[10000]=0;
    _map[20000]=0;
    _map[50000]=0;
    _map[100000]=0;
    _map[200000]=0;
    _map[500000]=0;
    std::map<int, int>::iterator i;
    std::ifstream fileIn;
    fileIn.open(path,std::ios_base::in);
    if(fileIn.is_open())
    {
        for(i=_map.begin(); i!=_map.end(); i++)
        {
            fileIn >> (i->second);
        }
    }
    else
        std::cout << "Can't open file." << "\n";
    fileIn.close();
    return _map;
}



void writeDataFromMapToFile(std::map<int,int> _map, const std::string& path)
{
    std::map<int, int>::iterator i;
    std::ofstream fileOut;
    fileOut.open(path,std::ios_base::out);
    if(fileOut.is_open())
    {
        for (i = _map.begin(); i != _map.end(); i++)
        {
            fileOut << (i->second) << "\n";
        }
    }
    else
        std::cout << "Can't open file." << "\n";
    fileOut.close();
}


void updateBalanceInFile(const std::string& _path,int newBalance)
{
    const char* path=_path.c_str();
    std::ofstream tempOut;
    tempOut.open("data\\temp.txt",std::ios_base::out);
    std::ifstream fileAccountIn;
    fileAccountIn.open(path,std::ios_base::in);
    if(tempOut.is_open())
    {
        tempOut << newBalance;
        int temp;
        fileAccountIn >> temp;
        while(!fileAccountIn.eof())
        {
            std::string line;
            getline(fileAccountIn,line);
            tempOut << line << "\n";
        }
        tempOut.seekp(-1,std::ios_base::cur);
    }
    else
        std::cout << "Can't open file.";
    fileAccountIn.close();
    tempOut.close();
    std::remove(path);
    rename("data\\temp.txt",path);
}


void goBack()
{
    char temp;
    std::cout << "Press 'b' to go back";
    do
    {
        temp=_getch();
    }
    while(temp!='b');
}
