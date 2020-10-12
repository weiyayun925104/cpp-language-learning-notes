#include <iostream>
#include <string>

using namespace std;

int main()
{
    string username1;
    int username1Age;

    cout << "Please enter a username and age.\n";
    cout << "Username: ";
    cin >> username1;
    cout << "Age: ";
    cin >> username1Age;

    string username2;
    int username2Age;

    cout << "Please enter another username and age.\n";
    cout << "Username: ";
    cin >> username2;
    cout << "Age: ";
    cin >> username2Age;

    if ( (username1Age > 100) && (username2Age > 100) )
    {
        cout << "Wow! Both users are really old!" << "\n";
    }

    if (username1Age > username2Age)
    {
        cout << username1 << " is older than " << username2 << "\n";
    }
    else if (username1Age < username2Age)
    {
        cout << username2 << " is older than " << username1 << "\n";
    }
    else
    {
        cout << username1 << " is the same age as " << username2 << "\n";
    }
}
