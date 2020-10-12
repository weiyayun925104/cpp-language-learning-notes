#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

map<string, double> &add_entry(map<string, double> &myMap);
map<string, double> &update_entry(map<string, double> &myMap);
map<string, double> &delete_entry(map<string, double> &myMap);
void display_entry(map<string, double> &myMap);
void print_all_entry(map<string, double> &myMap);
void get_all_entry(map<string, double> &myMap, vector<string> &entrys);

int main()
{
    map<string, double> myMap;

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
            cout << "Display high scores\n";
            print_all_entry(myMap);
            break;
        case 2:
            myMap = update_entry(myMap);
            cout << "Display high scores\n";
            print_all_entry(myMap);
            break;
        case 3:
            myMap = delete_entry(myMap);
            cout << "Display high scores\n";
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

void print_all_entry(map<string, double> &myMap)
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

void get_all_entry(map<string, double> &myMap, vector<string> &entrys)
{
    for (map<string, double>::iterator itr = myMap.begin(), end = myMap.end(); itr != end; ++itr)
    {
        entrys.push_back ( itr->first + " | " + to_string ( itr->second ) );
    }
}


void display_entry(map<string, double> &myMap)
{
    string name = "";
    map<string, double>::iterator itr;

    do
    {
        name = "";
        cout << "Please enter a name to display:\n";
        getline(cin, name, '\n');
        if (name == "")
        {
            break;
        }

        if ( ( itr = myMap.find(name) ) == myMap.end() )
        {
            cout << "The name doesn't exist.\n";
            continue;
        }

        cout << '\n';
        cout << name << " | " << to_string ( itr->second ) << "\n\n";
    }
    while (name != "");
}

map<string, double> &add_entry(map<string, double> &myMap)
{
    string name = "";
    double score = 0.0;
    map<string, double>::iterator itr;

    do
    {
        name = "";
        cout << "Please enter a name:\n";
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
        score = 0.0;
        cout << "Please enter an score for the name:\n";
        cin >> score;
        cin.clear();
        cin.ignore(80, '\n');


        myMap[name] = score;
        cout << "\n\n";
    }
    while (name != "");

    return myMap;
}

map<string, double> &update_entry(map<string, double> &myMap)
{
    string name = "";
    double score = 0.0;
    map<string, double>::iterator itr;

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
            cout << "The name doesn't exist.\n";
            cout << "Please enter an existing name to update.\n";
            continue;
        }
        score = 0.0;
        cout << "Please enter a new score for the name:\n";
        cin >> score;
        cin.clear();
        cin.ignore(80, '\n');

        itr->second = score;
        cout << "\n\n";
    }
    while (name != "");

    return myMap;
}

map<string, double> &delete_entry(map<string, double> &myMap)
{
    string name = "";
    map<string, double>::iterator itr;

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
            cout << "The name doesn't exist.\n";
            cout << "Please enter an existing name to delete.\n";
            continue;
        }

        myMap.erase(itr);
        cout << name << " has been removed.\n\n";
    }
    while (name != "");

    return myMap;
}
