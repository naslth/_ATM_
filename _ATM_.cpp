#include"_ATM_.h"
void user::logIn() {
    cout << "Please fill your ID: ";
    cin >> id;
    cout << "Please fill your password: ";
    cin >> pass;
}
bool user::checkAccount(const string& path) {
    ifstream fileIn;
    fileIn.open(path,ios_base::in);
    if(fileIn.is_open()) {
        while (!fileIn.eof()) {
            user test;
            fileIn >> test.id;
            fileIn >> test.pass;
            if(test.id == id && test.pass == pass) return true;
        }
    }
    else cout << "Can't open file.";
    fileIn.close();
    return false;
}
bool logInsuccessfully(user test) {
    int check=5;
    while(!test.checkAccount("listAccount.txt")) {
        check--;
        if (check == 0) return false;
        cout << "Your ID or password is incorrect. Please try again!" << "\n";
        if(check!=1) cout << "You have " << check << " attempts left." << "\n";
        else cout << "You have " << check << " attempt left." << "\n";
        test.logIn();
    }
    return true;
}
void showMenu() {
    cout << "-------------MENU-------------" << "\n";
    cout << "    1.   Transaction history  " << "\n";
    cout << "    2.   Check your balance   " << "\n";
    cout << "    3.   Deposit              " << "\n";
    cout << "    4.   Withdraw             " << "\n";
    cout << "    5.   Log out              " << "\n";
    cout << "------------------------------" << "\n" << "\n";
    cout << "    Please choose an option: ";
}
int checkBalance(user test){
    int balance = test.value[10000]*10000+test.value[20000]*20000+test.value[50000]*50000
                 +test.value[100000]*100000+test.value[200000]*200000+test.value[500000]*500000;
    return balance;
}
