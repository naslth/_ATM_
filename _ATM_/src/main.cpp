#include "../include/_ATM_.h"
#include "../include/showScreen.h"

#define WIDTH 95
#define HEIGHT 35
const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};


int main()
{
    setConsoleScreen(WIDTH,HEIGHT);

    bool exit = false;
    while(!exit)
    {
        int answer=showDisplayAndChooseOpt(WIDTH,HEIGHT); //In ra màn hình của cây ATM và chọn option
//Đăng ký tài khoản mới
        if(answer==1)
        {
            cout << "Please wait a second to go to sign up process..." << "\n";
            Sleep(1000);
            string accountInfo="";
            User temp;
            string tempID;
            string tempPass;
            string passcf;
            while(true)
            {
                system("cls");
                cout << "Please register in here. There are some requirement: " << "\n"
                     << "Username: " << "\n"
                     << "   - Must be at least 8 characters but not more than 20." << "\n"
                     << "   - You can use letters, numbers, underscores, periods, and the @ symbol." << "\n"
                     << "Password: " << "\n"
                     << "   - Must be at least 8 characters but not more than 20." << "\n"
                     << "   - Must contain at least one uppercase letter and one number."  << "\n"
                     << "REMEMBER that both username and password MUST NOT contain spaces." << "\n\n";
                cout << "   Enter your ID: ";
                getline(cin,tempID);
                cout << "   Enter your password: ";
                tempPass=maskingPass();
                temp.setInfo(tempID,tempPass);
                cout << "\n";
                cout << "   Confirm your pass word: ";
                passcf=maskingPass();
                cout << "\n";
// Kiểm tra tài khoản hợp lệ không
                if(!is_ID_Valid(tempID))
                {
                    cout << "Your ID is invalid. Please try again!" << "\n";
                    Sleep(700);
                }
                else if(!is_Pass_Valid(tempPass))
                {
                    cout << "Your password is invalid. Please try again!" << "\n";
                    Sleep(700);
                }
                else if(passcf!=tempPass)
                {
                    cout << "Password confirmation is not match. Please try again!" << "\n";
                    Sleep(700);
                }
                else if(temp.is_ID_In_ListAccount())
                {
                    cout << "Your ID already exists. Please try again!" << "\n";
                    Sleep(700);
                }
// Nếu chưa tồn tại thì ghi vào file danh sách tài khoản
                else
                {
                    fstream fileListAccount;
                    fileListAccount.open("data\\listAccount.txt",ios_base::app);
                    if(fileListAccount.is_open())
                    {
                        fileListAccount << tempID << "\n";
                        fileListAccount << tempPass << "\n";
                    }
                    else
                        cout << "Can't open file.";
                    fileListAccount.close();
                    break;
                }
            }
// Tạo file chứa thông tin của tài khoản vừa đăng ký và ghi vào số dư hiện tại (0 VND)
            accountInfo="data\\" + tempID + "Info.txt";
            ofstream fileAccountInfo;
            fileAccountInfo.open(accountInfo,ios_base::out);
            if(!fileAccountInfo.is_open())
                cout << "Can't open file.";
            else
                fileAccountInfo << "0";
            fileAccountInfo.close();
            cout << "Please wait a second..." << "\n\n";
            Sleep(1000);
            cout << "Sign up successfully." << "\n";
            cout << "   Your ID is: " << tempID << "\n";
            cout << "   Your password is: " << tempPass << "\n\n";
            cout << "Please wait a second and log in to your account..." << "\n";
            Sleep(2000);
            system("cls");
        }
//Đăng nhập vào tài khoản
        else if(answer==2)
        {
            cout << "Please wait a second to go to log in process...";
            Sleep(1000);
            system("cls");
            User test;
            string testID;
            string testPass;
            cout << "Enter your ID: ";
            getline(cin,testID);
            cout << "Enter your password: ";
            testPass=maskingPass();
            cout << "\n";
            test.setInfo(testID,testPass);
// Nếu đăng nhập thành công thì mở MENU
            if(test.is_Login_Successfully())
            {
                map<int,int> ATM_money;
                map<int, int>::iterator i;
//Khởi tạo map chứa thông tin về số tờ của các mệnh giá trong ATM
                for(int j=0; j<6; j++)
                {
                    ATM_money[moneyArr[j]]=0;
                }
                cout << "Please wait a second..." << "\n";
                Sleep(1000);
                cout << "Log in successfully!" << "\n";
                Sleep(1000);
                const string accountInfo="data\\" + testID + "Info.txt"; // khởi tạo đường dẫn đến file thông tin tài khoản
                bool logOut = false;
                while(!logOut)
                {
                    system("cls");
                    int menuOpt=showMenuAndChooseOpt(WIDTH,HEIGHT);
                    cout << "Please wait a second..." << "\n";
                    Sleep(1000);
                    switch(menuOpt)
                    {
// Show lịch sử giao dịch
                    case 1:
                    {
                        while(true)
                        {
                            system("cls");
                            int hOpt=showOptAndChoose(WIDTH,HEIGHT,1);
                            if(hOpt==1)
                            {
                                cout << "\t\t\t\t Transaction history" << "\n\n";
                                test.checkTransHistory(accountInfo);
                                goBack();
                            }
                            if(hOpt==2)
                                break;
                        }
                        break;
                    }
// Show số dư tài khoản
                    case 2:
                    {
                        while(true)
                        {
                            system("cls");
                            int bOpt=showOptAndChoose(WIDTH,HEIGHT,2);
                            if(bOpt==1)
                            {
                                int balance;
                                balance=test.checkBalance(accountInfo);
                                test.setBalance(balance);
                                cout << "Your balance is: " << balance << " VND." << "\n";
                                goBack();
                            }
                            if(bOpt==2)
                                break;
                        }
                        break;
                    }
// Nạp tiền vào tài khoản
                    case 3:
                    {
                        while(true)
                        {
                            system("cls");
                            int dOpt=showOptAndChoose(WIDTH,HEIGHT,3);
                            if(dOpt==1)
                            {
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
                                int denominations;
                                int bills;
                                bool checkDenominations=false;
// Nhập mệnh giá tiền và số tờ tiền. Kiểm tra mệnh giá hợp lệ hay không
                                do
                                {
                                    cout << "Enter the denominations: ";
                                    cin >> denominations;
                                    for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                                    {
                                        if((i->first)==denominations)
                                            checkDenominations=true;
                                    }
                                    if(!checkDenominations)
                                        cout << "The face value must be 10000, 20000, 50000, 100000, 200000, 500000 (VND). Try again!" << "\n";
                                }
                                while(!checkDenominations);
                                cout << "Enter the bills: ";
                                cin >> bills;
                                cin.ignore();
                                int moneyDeposit=denominations*bills;
// Đọc số dư từ file, tăng số tiền và cập nhật lại vào file
                                test.Deposit(accountInfo,moneyDeposit);
                                int currentBalance=test.checkBalance(accountInfo);
                                test.setBalance(currentBalance);
                                cout << "Please wait a second..." << "\n";
                                Sleep(1000);
                                cout << "Deposit successfully. Your current balance is: " << currentBalance << " VND" << "\n";
// Đọc thông tin trong cây ATM, tăng số tờ và cập nhật lại vào file;
                                ATM_money=readDataFromFileToMap("data\\ATMinfo.txt");
                                fstream fileATM;
                                for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                                {
                                    if((i->first)==denominations)
                                        (i->second)+=bills;
                                }
                                writeDataFromMapToFile(ATM_money,"data\\ATMinfo.txt");
                                goBack();
                            }
// Trở về MENU
                            if(dOpt==2)
                                break;
                        }
                        break;
                    }
// Rút tiền từ cây ATM
                    case 4:
                    {
                        while(true)
                        {
                            system("cls");
                            int wOpt=showOptAndChoose(WIDTH,HEIGHT,4);
// Rút tiền
                            if(wOpt==1)
                            {
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
// Đọc số dư tài khoản, đọc số tờ có trong cây ATM
                                ATM_money=readDataFromFileToMap("data\\ATMinfo.txt");
                                int balance=test.checkBalance(accountInfo);
                                test.setBalance(balance);
                                int minwithdraw;
// Kiểm tra trong cây ATM số tiền nhỏ nhất có thể rút được
                                for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                                {
                                    if((i->second)!=0)
                                    {
                                        minwithdraw=(i->first);
                                        break;
                                    }
                                }
                                int withdraw;
                                cout << "Your current balance is: " << balance << " VND." << "\n";
                                cout << "How much do you want to withdraw? ";
                                cin >> withdraw;
                                cin.ignore();
// Nhập số tiền rút, nếu số tiền rút nhỏ hơn số tiền nhỏ nhất có thể rút
//                  hoặc số tiền rút không phải bội số của 10000 thì quay lại
                                if(withdraw<minwithdraw)
                                {
                                    cout << "The smallest amount that can be withdrawn is: " << minwithdraw << " VND . Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(withdraw%10000!=0)
                                {
                                    cout << "Not enough change to withdraw! The withdrawal amount must be a multiple of 10000 VND. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else
                                {
                                    test.Withdraw(accountInfo,withdraw);
                                }
                            }
// trở về MENU
                            if(wOpt==2)
                                break;
                        }
                        break;
                    }
// Chuyển tiền cho tài khoản khác
                    case 5:
                    {
                        while(true)
                        {
                            system("cls");
                            int tOpt=showOptAndChoose(WIDTH,HEIGHT,5);
                            if(tOpt==1)
                            {
                                User accountReceive;
                                string accountReceiveID;
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
                                cout << "Enter username (ID) you want to transfer: ";
                                getline(cin,accountReceiveID);
                                accountReceive.setInfo(accountReceiveID,"0");
                                cout << "Enter amount you want to transfer: ";
                                int amount;
                                cin >> amount;
                                cin.ignore();
                                int balance=test.checkBalance(accountInfo);
                                test.setBalance(balance);
                                if(!is_ID_Valid(accountReceiveID))
                                {
                                    cout << "Username is invalid. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(balance-amount<0)
                                {
                                    cout << "Your balance is not enough money. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(!accountReceive.is_ID_In_ListAccount())
                                {
                                    cout << "Username not found! Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else
                                {
                                    tranfer(test,accountReceive,amount);
                                    cout << "Please wait a second..." << "\n";
                                    Sleep(1000);
                                    cout << "Transfer successful." << "\n";
                                    goBack();
                                }
                            }
                            if(tOpt==2)
                                break;
                        }
                        break;
                    }
// Đổi mật khẩu
                    case 6:
                    {
                        while(true)
                        {
                            system("cls");
                            int pOpt=showOptAndChoose(WIDTH,HEIGHT,6);
                            if(pOpt==1)
                            {
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
                                string currentpass;
// Nhập mật khẩu hiện tại
                                cout << "Enter your current password: ";
                                currentpass=maskingPass();
                                cout << "\n";
// Nếu đúng mật khẩu thì bắt đầu đổi mật khẩu
                                if(currentpass==testPass)
                                {
                                    string newPass;
                                    string newPasscf;
                                    cout << "Enter your new password: ";
                                    newPass=maskingPass();
                                    cout << "\n";
                                    cout << "Confirm your new password: ";
                                    newPasscf=maskingPass();
                                    cout << "\n";
// Kiểm tra mật khẩu mới có hợp lệ không
                                    if(!is_Pass_Valid(newPass))
                                        cout << "Your new password is invalid. Please try again!" << "\n";
                                    else if(newPass!=newPasscf)
                                        cout << "Password confirmation is not match. Please try again!" << "\n";

//Đổi mật khẩu và thoát tài khoản để đăng nhập lại
                                    else
                                    {
                                        test.changePass(newPass);
                                        test.setInfo(testID,newPass);
                                        cout << "Please wait a second..." << "\n";
                                        Sleep(1000);
                                        cout << "Your password is changed. Please log in again!";
                                        Sleep(2000);
                                        logOut=true;
                                        break;
                                    }
                                }
// Nếu mật khẩu không hợp lệ thì trở lại
                                else
                                {
                                    cout << "Your password is incorrect. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                            }
// trở về MENU
                            else if(pOpt==2)
                                break;
                        }
                        break;
                    }
// Thoát tài khoản
                    case 7:
                    {
                        system("cls");
                        int eOpt=showOptAndChoose(WIDTH,HEIGHT,7);
                        if(eOpt==1)
                        {
                            cout << "Please wait a second..." << "\n";
                            Sleep(1000);
                            system("cls");
                            cout << "Thank you for using my ATM! See you next time!" << "\n";
                            Sleep(2000);
                            system("cls");
                            logOut=true;
                            break;
                        }
                        else if(eOpt==2)
                            break;
                    }
                    default:
                        break;
                    }
                }
            }
// Nếu đăng nhập không thành công (quá 5 lần) thì sẽ bị khóa thẻ (thoát khỏi chương trình)
            else
            {
                cout << "You have tried to log in too many times" << "\n";
                cout << "Card is deactivated, please try after 1 minute.";
                exit=true;
            }
        }
// Thoát khỏi chương trình
        else if(answer==3)
        {
            exit=true;
        }
    }
    return 0;
}