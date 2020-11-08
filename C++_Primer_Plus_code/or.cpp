#include <iostream>

using namespace std;

int main()
{
    cout << "This program may reformat your hard disk and destroy all your data.\n";
    cout << "Do you wish to continue? <y/n> ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y')
    {
        cout << "You were warned!\n";
    }
    else if (ch == 'n' || ch == 'N')
    {
        cout << "A wise choice, bye.\n";
    }
    else
    {
        cout << "please enter a y or n\n";
    }

    return 0;
}
