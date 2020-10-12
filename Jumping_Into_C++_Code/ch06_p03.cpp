
#include <iostream>
#include <string>

using namespace std;

string promptUsername();
string promptPassword();
bool isValidLogin(string userName, string password);

int main()
{
    string userName = "";
    string password = "";
    size_t maxAttempts = 5;
    bool loginSuccessful = false;

    for (size_t i = 0; i < maxAttempts; i++)
    {
        if (i > 0)
        {
            cout << "Bad username or password. Denied access! Try again... (" << i + 1 << " of " << maxAttempts << ")\n";
        }

        userName = promptUsername();
        password = promptPassword();
        if(isValidLogin(userName, password))
        {
            loginSuccessful = true;
            break;
        }
    }

    if (loginSuccessful)
    {
        cout << "Access allowed" << "\n";
    }
    else
    {
        cout << "Bad username or password. Denied access! You're outta here!" << "\n";
        return 0;
    }
}

string promptUsername()
{
    string username;

    cout << "Enter your username: " << "\n";
    getline(cin, username, '\n');
    return username;
}

string promptPassword()
{
    string password;

    cout << "Enter your password: " << "\n";
    getline(cin, password, '\n');
    return password;
}

bool isValidLogin(string userName, string password)
{
    string username1 = "root";
    string password1 = "guest";
    string username2 = "Mark";
    string password2 = "Thomas";

    return ( ( (userName == username1) && (password == password1) ) ||
             ( (userName == username2) && (password == password2) ) );
}
