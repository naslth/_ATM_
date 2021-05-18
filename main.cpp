#include "_ATM_.h"

int main()
{
    const int moneyArr[6]= {10000,20000,50000,100000,200000,500000};
    bool exit = false;
    while(!exit)
    {
//In ra màn hình của cây ATM
        cout << "   THIS IS MY ATM!!    " << "\n";
        cout << "Do you have your account yet?" << "\n";
        cout << "1. No, I want to sign up for an account" << "\n";
        cout << "2. Yes, I want to log in to my account" << "\n";
        cout << "3. Exit" << "\n";
        cout << "Choose your option: ";
        int answer;
        cin >> answer;
        while(answer<1||answer>3)
        {
            cout << "Your option is invalid. Please choose another option!" << "\n";
            cout << "Choose your option: ";
            cin >> answer;
        }
//Đăng ký tài khoản mới
        if(answer==1)
        {
            cout << "Please wait a second to go to sign up process..." << "\n";
            Sleep(1000);
            string accountInfo="";
            User temp;
            cin.ignore();
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
                     << "REMEMBER that both username and password MUST NOT contain spaces." << "\n";
                string passcf;
                cout << "Enter your ID: ";
                getline(cin,temp.id);
                cout << "Enter your password: ";
                getline(cin,temp.pass);
                cout << "Confirm your pass word: ";
                getline(cin,passcf);
// Kiểm tra tài khoản hợp lệ không và đã tồn tại chưa
                if(!is_ID_Valid(temp.id))
                {
                    cout << "Your ID is invalid. Please try again!" << "\n";
                    Sleep(700);
                }
                else if(!is_Pass_Valid(temp.pass))
                {
                    cout << "Your password is invalid. Please try again!" << "\n";
                    Sleep(700);
                }
                else if(passcf!=temp.pass)
                {
                    cout << "Password confirmation is not match. Please try again!" << "\n";
                    Sleep(700);
                }
                else if(is_ID_In_ListAccount(temp.id))
                {
                    cout << "Your ID already exists. Please try again!" << "\n";
                    Sleep(700);
                }
// Nếu chưa tồn tại thì ghi vào file danh sách tài khoản và thoát ra
                else
                {
                    fstream fileListAccount;
                    fileListAccount.open("listAccount.txt",ios_base::out | ios_base::app);
                    if(fileListAccount.is_open())
                    {
                        fileListAccount << temp.id << "\n";
                        fileListAccount << temp.pass << "\n";
                    }
                    else
                        cout << "Can't open file.";
                    fileListAccount.close();
                    break;
                }
            }
// Tạo file chứa thông tin của tài khoản vừa đăng ký và ghi vào số dư hiện tại (0 VND)
            accountInfo=temp.id + "Info.txt";
            ofstream fileAccountInfo;
            fileAccountInfo.open(accountInfo,ios_base::out);
            if(!fileAccountInfo.is_open())
                cout << "Can't open file.";
            else
                fileAccountInfo << "0";
            fileAccountInfo.close();
            cout << "Please wait a second..." << "\n";
            Sleep(1000);
            cout << "Sign up successfully." << "\n";
            cout << "Your ID is: " << temp.id << "\n";
            cout << "Your password is: " << temp.pass << "\n";
            cout << "Please wait a second and log in to your account..." << "\n";
            Sleep(2000);
            system("cls");
        }
//Đăng nhập vào tài khoản
        else if(answer==2)
        {
            cout << "Please wait a second to go to log in process..." << "\n";
            Sleep(1000);
            system("cls");
            User test;
            cin.ignore();
            test.logIn();
// Nếu đăng nhập thành công thì mở MENU
            if(is_Login_Successfully(test))
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
                const string accountInfo=test.id+"Info.txt"; // khởi tạo đường dẫn đến file thông tin tài khoản
                int menuOpt;
                bool logOut=false;
                while(!logOut)
                {
                    system("cls");
                    showMenu();
                    do
                    {
                        cin >> menuOpt;
                        if(menuOpt<1||menuOpt>7)
                            cout << "Invalid selection. Please choose another option: ";
                    }
                    while(menuOpt<1||menuOpt>7);
                    cout << "Please wait a second..." << "\n";
                    Sleep(1000);
                    switch(menuOpt)
                    {
// Show lịch sử giao dịch
                    case 1:
                    {
                        cout << "This is your transaction history: " << "\n";
                        checkTransHistory(accountInfo);
                        char temp;
                        cout << "Enter 'b' to go back: ";
                        do
                        {
                            cin >> temp;
                        }
                        while(temp!='b');
                        break;
                    }
// Show số dư tài khoản
                    case 2:
                    {
                        int balance;
                        balance=checkBalance(accountInfo);
                        cout << "Your balance is: " << balance << " VND." << "\n";
                        char temp;
                        cout << "Enter 'b' to go back: ";
                        do
                        {
                            cin >> temp;
                        }
                        while(temp!='b');
                        break;
                    }
// Nạp tiền vào tài khoản
                    case 3:
                    {
                        while(true)
                        {
                            system("cls");
                            int dOpt;
                            cout << "Choose an option: " << "\n";
                            cout << "1. Deposit         2. Return" << "\n";
                            cout << "Choose your option: ";
                            do
                            {
                                cin >> dOpt;
                                if(dOpt!=1&&dOpt!=2)
                                    cout << "Invalid selection. Please choose another option: ";

                            }
                            while(dOpt!=1&&dOpt!=2);
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
                                int moneyDeposit=denominations*bills;
// Đọc số dư từ file, tăng số tiền và cập nhật lại vào file
                                Deposit(accountInfo,test,moneyDeposit);
                                int currentBalance=checkBalance(accountInfo);
                                cout << "Please wait a second..." << "\n";
                                Sleep(1000);
                                cout << "Deposit successfully. Your current balance is: " << currentBalance << " VND" << "\n";
// Đọc thông tin trong cây ATM, tăng số tờ và cập nhật lại vào file;
                                ATM_money=readDataFromFileToMap("ATMinfo.txt");
                                fstream fileATM;
                                for (i = ATM_money.begin(); i != ATM_money.end(); i++)
                                {
                                    if((i->first)==denominations)
                                        (i->second)+=bills;
                                }
                                writeDataFromMapToFile(ATM_money,"ATMinfo.txt");
                                char temp;
                                cout << "Enter 'b' to go back: ";
                                do
                                {
                                    cin >> temp;
                                }
                                while(temp!='b');
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
                            cout << "Choose an option: " << "\n";
                            cout << "1. Withdraw         2. Return" << "\n";
                            cout << "Choose your option: ";
                            int wOpt;
                            do
                            {
                                cin >> wOpt;
                                if(wOpt!=1&&wOpt!=2)
                                    cout << "Invalid selection. Please choose another option: ";
                            }
                            while(wOpt!=1&&wOpt!=2);
// Rút tiền
                            if(wOpt==1)
                            {
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
// Đọc số dư tài khoản, đọc số tờ có trong cây ATM
                                ATM_money=readDataFromFileToMap("ATMinfo.txt");
                                test.balance=checkBalance(accountInfo);
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
                                cout << "Your current balance is: " << test.balance << " VND." << "\n";
                                cout << "How much do you want to withdraw? ";
                                cin >> withdraw;
// Nhập số tiền rút, nếu số tiền rút nhỏ hơn số tiền nhỏ nhất có thể rút
//                  hoặc số tiền rút không phải bội số của số tiền nhỏ nhất có thể rút thì quay lại
                                if(withdraw<minwithdraw)
                                {
                                    cout << "The smallest amount that can be withdrawn is: " << minwithdraw << " VND . Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(withdraw%minwithdraw!=0)
                                {
                                    cout << "Not enough change to withdraw! The withdrawal amount must be a multiple of " << minwithdraw << " . Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else
                                {
                                    Withdraw(accountInfo,test,withdraw);
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
                            cout << "Do you want to tranfer?" << "\n";
                            cout << "1. Yes       2. Return" << "\n";
                            cout << "Choose your option: ";
                            int tOpt;
                            do
                            {
                                cin >> tOpt;
                                if(tOpt<1||tOpt>2)
                                    cout << "Invalid selection. Please choose another option: ";
                            }
                            while(tOpt<1||tOpt>2);
                            if(tOpt==1)
                            {
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
                                cout << "Enter username (ID) you want to transfer: ";
                                string accountReceive;
                                cin.ignore();
                                getline(cin,accountReceive);
                                cout << "Enter amount you want to transfer: ";
                                int amount;
                                cin >> amount;
                                test.balance=checkBalance(accountInfo);
                                if(!is_ID_Valid(accountReceive))
                                {
                                    cout << "Username is invalid. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(test.balance-amount<0)
                                {
                                    cout << "Your balance is not enough money. Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else if(!is_ID_In_ListAccount(accountReceive))
                                {
                                    cout << "Username not found! Please try again!" << "\n";
                                    Sleep(1000);
                                }
                                else
                                {
                                    tranfer(test.id,accountReceive,test.balance,amount);
                                    cout << "Please wait a second..." << "\n";
                                    Sleep(1000);
                                    cout << "Transfer successful. Enter 'b' to go back: ";
                                    char temp;
                                    do
                                    {
                                        cin >> temp;
                                    }
                                    while(temp!='b');
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
                            cout << "Do you want to change password?" << "\n";
                            cout << "1. Yes       2. Return" << "\n";
                            cout << "Choose your option: ";
                            int pOpt;
                            do
                            {
                                cin >> pOpt;
                                if(pOpt<1||pOpt>2)
                                    cout << "Invalid selection. Please choose another option: ";

                            }
                            while(pOpt<1||pOpt>2);
                            if(pOpt==1)
                            {
                                cout << "Please wait a second to go to process..."<< "\n";
                                Sleep(1000);
                                system("cls");
                                cin.ignore();
                                string currentpass;
// Nhập mật khẩu hiện tại
                                cout << "Enter your current password: ";
                                getline(cin,currentpass);
// Nếu đúng mật khẩu thì bắt đầu đổi mật khẩu
                                if(currentpass==test.pass)
                                {
                                    string newPass;
                                    string newPasscf;
                                    cout << "Enter your new password: ";
                                    getline(cin,newPass);
                                    cout << "Confirm your new password: ";
                                    getline(cin,newPasscf);
// Kiểm tra mật khẩu mới có hợp lệ không
                                    if(!is_Pass_Valid(newPass))
                                        cout << "Your new password is invalid. Please try again!" << "\n";
                                    else if(newPass!=newPasscf)
                                        cout << "Password confirmation is not match. Please try again!" << "\n";

//Đổi mật khẩu và thoát tài khoản để đăng nhập lại
                                    else
                                    {
                                        changePass(test.id,newPass);
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
                        cout << "Choose an option: " << "\n";
                        cout << "1. Log out       2. Return" << "\n";
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
