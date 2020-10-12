
#include <iostream>
#include <string>

using namespace std;

struct Person
{
    string name;
    string address;
    string phoneNumber;
};

int const maxNumberOfEntries = 50;

int main()
{
    int numberOfEntries;
    cout << "Please specify between 1 and " << maxNumberOfEntries << " the number of address book entries that you want to fill...\n";
    cin >> numberOfEntries;
    cin.clear();
    cin.ignore(80, '\n'); 

    if (numberOfEntries < 1)
    {
        numberOfEntries = 1;
    }

    Person people[maxNumberOfEntries];

    int actualNumberOfEntries = 0;
    for (int i = 0; i < maxNumberOfEntries; i++)
    {
        string temp;

        cout << "Please fill out # " << i + 1 << " of " << numberOfEntries << " entries.\n";
        cout << "Please enter your name:\n";
        getline(cin, people[i].name, '\n');

        cout << "Please enter your address:\n";
        getline(cin, people[i].address, '\n');

        cout << "Please enter your phone number:\n";
        getline(cin, people[i].phoneNumber, '\n');

        string addMore;
        cout << "Would you like to add another name? (Y/N)\n";
        cin >> addMore;
        cin.clear();
        cin.ignore(80, '\n'); 

        actualNumberOfEntries++;
        if (addMore == "N")
        {
            break;
        }
    }

    cout << "Writing out contents of address book:\n";
    cout << "=====================\n";
    for (int i = 0; i < actualNumberOfEntries; i++)
    {
        cout << "Entry # " << i + 1 << '\n';
        cout << "Your name is: " << people[i].name << '\n';
        cout << "Your address is: " << people[i].address << '\n';
        cout << "Your phone number is: " << people[i].phoneNumber << '\n';
        cout << "=====================\n";
    }
}
