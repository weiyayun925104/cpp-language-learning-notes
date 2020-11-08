#include <iostream>

using namespace std;

const int Max = 5;

int main()
{
    double golf[Max];
    cout << "Please enter your golf scores.\n";
    cout << "You must enter " << Max << " rounds.\n";
    int i;
    for (i = 0; i < Max; i++)
    {
        cout << "round #" << i + 1 << ": ";
        while (!(cin >> golf[i]))
        {
            cin.clear();
            while (cin.get() != '\n')
            {
                continue;
            }
            cout << "Please enter a number: ";
        }
        while (cin.get() != '\n')
        {
            continue;
        }
    }

    double total = 0.0;
    for (i = 0; i < Max; i++)
    {
        total += golf[i];
    }

    cout << "average score of " << Max << " rounds = " << total / Max << endl;

    return 0;
}
