#include <iostream>
#include <string>

using namespace std;

void getNameByPointer(string *firstName, string *lastName)
{
    cout << "Please enter your first name: ";
    cin >> *firstName;

    cout << "Please enter your last name: ";
    cin >> *lastName;
}

void getNameByReference(string &firstName, string &lastName)
{
    cout << "Please enter your first name: ";
    cin >> firstName;

    cout << "Please enter your last name: ";
    cin >> lastName;
}

int main()
{
    string firstName;
    string lastName;

    getNameByPointer(&firstName, &lastName);
    cout << "Your name is " << firstName << " " << lastName << '\n';

    getNameByReference(firstName, lastName);
    cout << "Your name is " << firstName << " " << lastName << '\n';
}
