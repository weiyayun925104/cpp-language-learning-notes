#include <iostream>
#include <string>

using namespace std;

string promptUsername()
{
    string username;

    cout << "Enter your username: ";
    getline(cin, username, '\n');
    return username;
}

string promptPassword()
{
    string password;

    cout << "Enter your password: ";
    getline(cin, password, '\n');
    return password;
}

int main()
{
    string username = promptUsername();
    string password = promptPassword();

    string username1 = "root";
    string password1 = "guest";
    string username2 = "Mark";
    string password2 = "Thomas";
    if ( ( (username == username1) && (password == password1) ) ||
            ( (username == username2) && (password == password2) ) )
    {
        cout << "Access allowed" << "\n";
    }
    else
    {
        cout << "Bad username or password. Denied access! Try again..." << "\n";
        username = promptUsername();
        password = promptPassword();

        if ( ( (username == username1) && (password == password1) ) ||
                ( (username == username2) && (password == password2) ) )
        {
            cout << "Access allowed" << "\n";
        }
        else
        {
            cout << "Bad username or password. Denied access! You're outta here!" << "\n";
            return 0;
        }
    }
}
