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
map<int,int> readDataFromFileToMap(const string& path){
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
    if(fileIn.is_open()) {
        for(i=_map.begin(); i!=_map.end(); i++) {
            fileIn >> (i->second);
        }
    }
    else cout << "Can't open file.";
    fileIn.close();
    return _map;
}
void writeDataFromMapToFile(map<int,int> _map, const string& path) {
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
    else cout << "Can't open file." << "\n";
    fileOut.close();
}
int checkBalance(user test, const string& path){
    test.value=readDataFromFileToMap(path);
    int balance = test.value[10000]*10000+test.value[20000]*20000+test.value[50000]*50000
                 +test.value[100000]*100000+test.value[200000]*200000+test.value[500000]*500000;
    return balance;
}
void checkTransHistory(const string& path) {
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
        if(i==0) cout << "Your transaction history is clear. Let make some transaction." << "\n";
    }
    else cout << "Can't open file.";
    fileAccountHistoryIn.close();
}
