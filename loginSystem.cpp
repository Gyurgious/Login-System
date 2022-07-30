#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// login and registration system for multiple accounts using files - saving and loading

bool checkPassword(string _password) { // checks if password is valid
    int checkUpper = 0;
    int checkInt = 0;

    for (int i = 0; i < _password.size(); i++) {
        if (isupper(_password[i])){
            checkUpper++;
        }

        if(isdigit(_password[i])) {
            checkInt++;
        }
    }
    return (checkUpper > 0 && checkInt > 0);
}


int main() {
    string username, newUsername, password, newPassword, fileData, readData;
    string accounts[100];
    int select;
    bool login = false;
    fileData = "database.txt";
    

    cout << "Welcome! Login or Create New Account?(1. Login, 2. Create new Account)" << endl;
    cin >> select;
    if (select == 1) { // login into account
        ifstream fin(fileData);
        
        int j = 0;
        while(getline(fin, readData)) { // storing file data in an array
            accounts[j] = readData;
            j++;
        }
        
        int count = 0;
        while (!login) {
            cout << "enter username: " << endl;
            cin >> username;
            cout << "enter password: " << endl;
            cin >> password;

            for (int i = 0; i < j; i++) { // scanning through each username and password stored in the file/array
                int pos = accounts[i].find(" ");
                int passwordSize = accounts[i].size() - pos;

                string fusername = accounts[i].substr(0, pos); // username stored in the file/array
                string fpassword = accounts[i].substr(pos+1, passwordSize); // password stored in the file/array

                if (username == fusername && password == fpassword) {
                    cout << "Account found! Hi " << username << "!" << endl;
                    login = true;
                    break;
                }
             }

            if (!login) {cout << "Invalid login! PLease try again." << endl;}
        
        }
    }

    else { // create an account

        while (!checkPassword(newPassword)) {
            cout << "enter username for new account: " << endl;
            cin >> newUsername;
            cout << "enter password for new account: " << endl;
            cin >> newPassword;
            if (!checkPassword(newPassword)) {cout << "Weak password! Password must contain at least one capital letter and a number." << endl;}
        }

        ofstream fout;
        fout.open(fileData, ios::app); // ios::app allows user to keep appending data to file
        fout << newUsername << " " << newPassword << endl;

        cout << "Account saved!" << endl;
        fout.close();
    }
}