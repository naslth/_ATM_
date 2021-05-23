#include "../include/_ATM_.h"
#include "../include/showScreen.h"
#include "mmsystem.h"

#define WIDTH 115
#define HEIGHT 45
const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};


int main()
{
    setConsoleScreen(WIDTH,HEIGHT);
    bool exit = false;
    int musicOpt=showMusicAndChooseOpt(WIDTH,HEIGHT);
    if (musicOpt==4) {
        PlaySound(NULL,NULL,SND_ASYNC | SND_LOOP);
    }
    while(!exit)
    {
        int answer=showDisplayAndChooseOpt(WIDTH,HEIGHT); //In ra màn hình của cây ATM và chọn option
//Đăng ký tài khoản mới
        if(answer==1)
        {
            cout << "Please wait a second to go to sign up process..." << "\n";
            Sleep(700);
            User temp;
            string tempID,tempPass,passcf,accountInfo;
            while(true)
            {
                system("cls");
                setColor(GREEN);
                cout << "Please register in here. There are some requirement: " << "\n"
                     << "Username: " << "\n"
                     << "   - Must be at least 8 characters but not more than 20." << "\n"
                     << "   - You can use letters, numbers, underscores, periods, and the @ symbol." << "\n"
                     << "Password: " << "\n"
                     << "   - Must be at least 8 characters but not more than 20." << "\n"
                     << "   - Must contain at least one uppercase letter and one number."  << "\n"
                     << "REMEMBER that both username and password MUST NOT contain spaces." << "\n\n";
                setColor(AQUA);
                cout << "\t\t\t\t\t\t  __          \n";
                cout << "\t\t\t\t\t\t (  `_    //  \n";
                cout << "\t\t\t\t\t\t__)/(//) (//) \n";
                cout << "\t\t\t\t\t\t   _/     /   \n\n";
                cout << "      Enter your ID: ";
                getline(cin,tempID);
                cout << "      Enter your password: ";
                tempPass=maskingPass();
                temp.setInfo(tempID,tempPass);
                cout << "\n";
                cout << "      Confirm your password: ";
                passcf=maskingPass();
                cout << "\n\n";
                setColor(WHITE);
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
                    bool is_List_Account_Clear=false;;
                    ifstream fileListAccountIn;
// Kiểm tra listAccount có rỗng không
                    fileListAccountIn.open("data\\listAccount.txt",ios_base::in);
                    if(fileListAccountIn.is_open())
                    {
                        fileListAccountIn.seekg(0, ios::end);
                        if (fileListAccountIn.tellg() == 0) {
                            is_List_Account_Clear=true;
                        }
                    }
                    else
                        cout << "Can't open file.";
                    fileListAccountIn.close();
                    ofstream fileListAccountOut;
                    fileListAccountOut.open("data\\listAccount.txt",ios_base::app);
                    if(fileListAccountOut.is_open())
                    {
                        if(is_List_Account_Clear) {
                            fileListAccountOut << tempID << "\n";
                            fileListAccountOut << tempPass << "\n";
                        }
                            else{
                        fileListAccountOut << "\n" << tempID << "\n";
                        fileListAccountOut << tempPass << "\n";
                            }
                    }
                    else
                        cout << "Can't open file.";
                    fileListAccountOut.close();
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
                fileAccountInfo << "0" << "\n";
            fileAccountInfo.close();
            cout << "Please wait a second..." << "\n\n";
            Sleep(700);
            cout << "Sign up successfully." << "\n";
            cout << "Please wait a second and log in to your account..." << "\n";
            Sleep(1500);
            system("cls");
        }
//Đăng nhập vào tài khoản
        else if(answer==2)
        {
            cout << "Please wait a second to go to log in process...";
            Sleep(700);
            system("cls");
            User test;
            string testID,testPass;
// Nếu đăng nhập thành công thì mở MENU
            if(test.is_Login_Successfully(WIDTH,HEIGHT))
            {
                system("cls");
                string testID=test.getID();
                string testPass=test.getPass();
                map<int,int> ATM_money;
                map<int, int>::iterator i;
//Khởi tạo map chứa thông tin về số tờ của các mệnh giá trong ATM
                for(int j=0; j<6; j++)
                {
                    ATM_money[moneyArr[j]]=0;
                }
                cout << "Please wait a second..." << "\n";
                Sleep(700);
                cout << "Log in successfully!" << "\n";
                Sleep(1000);
                const string accountInfo="data\\" + testID + "Info.txt"; // khởi tạo đường dẫn đến file thông tin tài khoản
                bool logOut = false;
                while(!logOut)
                {
                    system("cls");
                    int menuOpt=showMenuAndChooseOpt(WIDTH,HEIGHT);
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
                                cout << "\t\t\t\t+-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+\n";
                                cout << "\t\t\t\t|T|r|a|n|s|a|c|t|i|o|n| |H|i|s|t|o|r|y|\n";
                                cout << "\t\t\t\t+-+-+-+-+-+-+-+-+-+-+-+ +-+-+-+-+-+-+-+";
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
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+\n";
                                cout << "\t\t\t\t\t|B|a|l|a|n|c|e|\n";
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+\n\n";
                                cout << "\t\tYour balance is: " << balance << " VND." << "\n\n";
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
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+\n";
                                cout << "\t\t\t\t\t|D|e|p|o|s|i|t|\n";
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+\n\n";
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
                                if(moneyDeposit>1000000000) {
                                    cout << "The amount deposited must less than 1 billion VND. Try again!" << "\n";
                                    Sleep(700);
                                }
// Đọc số dư từ file, tăng số tiền và cập nhật lại vào file
                                else{
                                    test.Deposit(accountInfo,moneyDeposit);
                                    int currentBalance=test.checkBalance(accountInfo);
                                    test.setBalance(currentBalance);
                                    cout << "Please wait a second..." << "\n\n";
                                    Sleep(1000);
                                    cout << "Deposit successfully. Your current balance is: " << currentBalance << " VND" << "\n\n";
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
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+-+\n";
                                cout << "\t\t\t\t\t|W|i|t|h|d|r|a|w|\n";
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+-+\n\n";
// Đọc số dư tài khoản, đọc số tờ có trong cây ATM
                                ATM_money=readDataFromFileToMap("data\\ATMinfo.txt");
                                int balance=test.checkBalance(accountInfo);
                                test.setBalance(balance);
                                int minwithdraw=10000;
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
                                    cout << "The smallest amount that can be withdrawn is " << minwithdraw << " VND . Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(withdraw%10000!=0)
                                {
                                    cout << "The withdrawal amount must be a multiple of 10000 VND. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(withdraw>1000000000) {
                                    cout << "The biggest amount that can be withdrawn is 1 billion VND. Plase try again!" << "\n";
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
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+-+\n";
                                cout << "\t\t\t\t\t|T|r|a|n|s|f|e|r|\n";
                                cout << "\t\t\t\t\t+-+-+-+-+-+-+-+-+\n\n";
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
                                else if(accountReceiveID==testID) {
                                    cout << "You can not transfer to yourself! Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else
                                {
                                    tranfer(test,accountReceive,amount);
                                    cout << "Please wait a second..." << "\n\n";
                                    Sleep(700);
                                    balance=test.checkBalance(accountInfo);
                                    test.setBalance(balance);
                                    cout << "Transfer successful. Your current balance is: " << balance <<" VND.\n\n";
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
                                cout << "\t\t\t\t+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+\n";
                                cout << "\t\t\t\t|C|h|a|n|g|e| |P|a|s|s|w|o|r|d|\n";
                                cout << "\t\t\t\t+-+-+-+-+-+-+ +-+-+-+-+-+-+-+-+\n\n";
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
                                    {
                                        cout << "Your new password is invalid. Please try again!" << "\n";
                                        Sleep(1000);
                                    }
                                    else if(newPass!=newPasscf)
                                    {
                                        cout << "Password confirmation is not match. Please try again!" << "\n";
                                        Sleep(1000);
                                    }
                                    else if(newPass==testPass)
                                    {
                                        cout << "The new password must be different from the current password" << "\n";
                                        Sleep(1000);
                                    }

//Đổi mật khẩu và thoát tài khoản để đăng nhập lại
                                    else
                                    {
                                        test.changePass(newPass);
                                        test.setInfo(testID,newPass);
                                        testPass=newPass;
                                        cout << "Please wait a second..." << "\n";
                                        Sleep(700);
                                        cout << "Your password is changed. Please log in again!";
                                        Sleep(1500);
                                        system("cls");
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
                            Sleep(700);
                            system("cls");
                            setColor(YELLOW);
                            cout << "\n\n\n\n\n\n\n\n\n\n";
                            cout <<"   _______ _                 _                           __                       _                                "
                                 <<"  |__   __| |               | |                         / _|                     (_)                               "
                                 <<"     | |  | |__   __ _ _ __ | | __  _   _  ___  _   _  | |_ ___  _ __   _   _ ___ _ _ __   __ _   ________  _   _  "
                                 <<"     | |  |  _ ` / _` |  _ `| |/ / | | | |/ _ `| | | | |  _/ _ `|  __| | | | / __| |  _ ` / _` | |  _   _ `| | | | "
                                 <<"     | |  | | | | (_| | | | |   <  | |_| | (_) | |_| | | || (_) | |    | |_| `__ ` | | | | (_| | | | | | | | |_| | "
                                 <<"     |_|  |_| |_|`__,_|_| |_|_|`_`  `__, |`___/ `__,_| |_| `___/|_|     `__,_|___/_|_| |_|`__, | |_| |_| |_|`__, | "
                                 <<"                                     __/ |                                                 __/ |             __/ | "
                                 <<"                                    |___/                                                 |___/             |___/  "
                                 <<"           _______ __  __            ____              _    _                _____           _                   _ "
                                 <<"        /`|__   __|  `/  |          |  _ `            | |  (_)              / ____|         | |                 | |"
                                 <<"       /  `  | |  | `  / |  ______  | |_) | __ _ _ __ | | ___ _ __   __ _  | (___  _   _ ___| |_ ___ ________   | |"
                                 <<"      / /` ` | |  | |`/| | |______| |  _ < / _` |  _ `| |/ / |  _ ` / _` |  `___ `| | | / __| __/ _ `  _   _ `  | |"
                                 <<"     / ___` `| |  | |  | |          | |_) | (_| | | | |   <| | | | | (_| |  ____) | |_| `__ ` ||  __/ | | | | | |_|"
                                 <<"    /_/    `_`_|  |_|  |_|          |____/ `__,_|_| |_|_|`_`_|_| |_|`__, | |_____/ `__, |___/`__`___|_| |_| |_| (_)"
                                 <<"                                                                    __/ |          __/ |                           "
                                 <<"                                                                   |___/          |___/                            ";
                            setColor(WHITE);
                            Sleep(2500);
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
                system("cls");
                gotoXY(WIDTH/2-20,HEIGHT/2-3);
                cout << "You have tried to log in too many times" << "\n";
                cout << "\t\t\tCard is deactivated, please try after 1 minute.";
                Sleep(2000);
                system("cls");
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
