#include <iostream>
#include <string>

using namespace std;

void getNameByPointer(string *firstName, string *lastName)
{
    cout << "Please enter your first name: ";
    cin >> *firstName;

    if ( lastName->empty() )
    {
        cout << "Please enter your last name: ";
        cin >> *lastName;
    }
}

void getNameByReference(string &firstName, string &lastName)
{
    cout << "Please enter your first name: ";
    cin >> firstName;

    if (lastName.empty())
    {
        cout << "Please enter your last name: ";
        cin >> lastName;
    }
}

int main()
{
    string firstName;
    string lastName;

    getNameByPointer(&firstName, &lastName);
    cout << "Your name is " << firstName << " " << lastName << '\n';
    cout << '\n';

    getNameByPointer(&firstName, &lastName);
    cout << "Your name is " << firstName << " " << lastName << '\n';
    cout << '\n';

    string firstName3;
    string lastName3;

    getNameByReference(firstName3, lastName3);
    cout << "Your name is " << firstName3 << " " << lastName3 << '\n';
    cout << '\n';

    getNameByReference(firstName3, lastName3);
    cout << "Your name is " << firstName3 << " " << lastName3 << '\n';
    cout << '\n';
}
