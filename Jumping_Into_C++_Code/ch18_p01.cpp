#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, string> &add_entry(map<string, string> &myMap);
map<string, string> &update_entry(map<string, string> &myMap);
map<string, string> &delete_entry(map<string, string> &myMap);
void display_entry(map<string, string> &myMap);
void print_all_entry(map<string, string> &myMap);
void get_all_entry(map<string, string> &myMap, vector<string> &entrys);

int main()
{
    map<string, string> myMap;

    bool exitProgram = false;
    int choice = 0;
    int numberOfNodes = 0;

    while (!exitProgram)
    {
        choice = 0;
        numberOfNodes = myMap.size();

        cout << "Please choose from the following options:\n";
        cout << "0. Exit\n";
        cout << "1. Add entry\n";
        if (numberOfNodes > 0)
        {
            cout << "2. Update entry\n";
            cout << "3. Delete entry\n";
            cout << "4. Display entry\n";
        }
        cin >> choice;
        cin.clear();
        cin.ignore(80, '\n');

        cout << '\n';

        switch (choice)
        {
        case 0:
            exitProgram = true;
            break;
        case 1:
            myMap = add_entry(myMap);
            cout << "Display address book\n";
            print_all_entry(myMap);
            break;
        case 2:
            myMap = update_entry(myMap);
            cout << "Display address book\n";
            print_all_entry(myMap);
            break;
        case 3:
            myMap = delete_entry(myMap);
            cout << "Display address book\n";
            print_all_entry(myMap);
            break;
        case 4:
            display_entry(myMap);
            break;
        default:
            exitProgram = true;
            break;
        }
    }

    myMap.clear();
}

void print_all_entry(map<string, string> &myMap)
{
    int numberOfNodes = myMap.size();
    if (numberOfNodes == 0)
    {
        return;
    }

    vector<string> entrys;
    get_all_entry(myMap, entrys);

    for (int i = 0; i < entrys.size(); i++)
    {
        cout << "key | value = " << entrys[i] << '\n';
    }
    cout << "\n\n";
}

void get_all_entry(map<string, string> &myMap, vector<string> &entrys)
{
    for (map<string, string>::iterator itr = myMap.begin(), end = myMap.end(); itr != end; ++itr)
    {
        entrys.push_back ( itr->first + " | " + itr->second );
    }
}


void display_entry(map<string, string> &myMap)
{
    string name = "";
    map<string, string>::iterator itr;

    do
    {
        name = "";
        cout << "Please enter a name from the address book to display:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( itr = myMap.find(name) ) == myMap.end() )
        {
            cout << "The name can not find in the address book.\n";
            continue;
        }

        cout << '\n';
        cout << name << " | " << itr->second << "\n\n";
    }
    while (name != "");
}

map<string, string> &add_entry(map<string, string> &myMap)
{
    string name = "";
    string email = "";
    map<string, string>::iterator itr;

    do
    {
        name = "";
        cout << "Please enter a name for the address book:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( itr = myMap.find(name) ) != myMap.end() )
        {
            cout << "The name already exists.\n";
            cout << "Please enter a unique name to add.\n";
            continue;
        }
        email = "";
        cout << "Please enter an email address for the name:\n";
        getline(cin, email, '\n');
        if (email == "")
        {
            break;
        }

        myMap[name] = email;
        cout << "\n\n";
    }
    while (name != "");

    return myMap;
}

map<string, string> &update_entry(map<string, string> &myMap)
{
    string name = "";
    string email = "";
    map<string, string>::iterator itr;

    do
    {
        name = "";
        cout << "Please enter a name to update:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( itr = myMap.find(name) ) == myMap.end() )
        {
            cout << "The name can not find in the address book.\n";
            cout << "Please enter an existing name to update.\n";
            continue;
        }
        email = "";
        cout << "Please enter a new email address for the name:\n";
        getline(cin, email, '\n');
        if (email == "")
        {
            break;
        }

        itr->second = email;
        cout << "\n\n";
    }
    while (name != "");

    return myMap;
}

map<string, string> &delete_entry(map<string, string> &myMap)
{
    string name = "";
    map<string, string>::iterator itr;

    do
    {
        name = "";
        cout << "Please enter a name to delete:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( itr = myMap.find(name) ) == myMap.end() )
        {
            cout << "The name can not find in the address book.\n";
            cout << "Please enter an existing name to delete.\n";
            continue;
        }

        myMap.erase(itr);
        cout << name << " has been removed from the address book.\n\n";
    }
    while (name != "");

    return myMap;
}
