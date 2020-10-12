
#include <iostream>
#include <string>

using namespace std;

struct Person
{
    string name;
    string address;
    string phoneNumber;
};

int main()
{
    Person person;

    cout << "Please enter your name:\n";
    getline(cin, person.name, '\n');

    cout << "Please enter your address:\n";
    getline(cin, person.address, '\n');

    cout << "Please enter your phone number:\n";
    getline(cin, person.phoneNumber, '\n');

    cout << "Your name is: " << person.name << '\n';
    cout << "Your address is: " << person.address << '\n';
    cout << "Your phone number is: " << person.phoneNumber << '\n';
}
