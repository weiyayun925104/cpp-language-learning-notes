#include <iostream>
#include <string>

using namespace std;

int main()
{
    string password = "guest";
    string userInput = "";
    int attemptLimit = 5;

    for (size_t attempts = 0; attempts < attemptLimit; attempts++)
    {
        if (attempts > 0)
        {
            cout << "You entered an incorrect password! \n" <<
                 "Attempts remaining: " << attemptLimit - attempts << "\n";
        }
        cout << "Please enter your password: " << "\n";
        cin >> userInput;
        if (userInput == password)
        {
            cout << "Congratulations! You have been granted access..." << "\n";
            return 0;
        }
    }
    cout << "Sadly we can't let you in. Goodbye :-( " << "\n";
    return 1;
}
