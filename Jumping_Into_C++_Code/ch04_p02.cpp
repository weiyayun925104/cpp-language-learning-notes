#include <iostream>

using namespace std;

int main()
{
    int password1 = 12345;
    int password2 = 54321;
    int userPassword = 0;

    cout << "Please enter a number for your password:\n";
    cin >> userPassword;
    if ( (userPassword == password1) || (userPassword == password2) )
    {
        cout << "Yay! You guessed correctly" << "\n";
    }
    else
    {
        cout << "Error! Bad password! Intruder alert!" << "\n";
        return 0;
    }
}
