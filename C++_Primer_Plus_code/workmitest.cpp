#include <iostream>
#include <cstring>
#include "workermi.h"

const int SIZE = 5;

int main()
{
    using std::cin;
    using std::cout;
    using std::endl;
    using std::strchr;

    Worker *lolas[SIZE];

    int ct;
    for (ct = 0; ct < SIZE; ct++)
    {
        char choice;
        cout << "Enter the employee category:\n"
             << "w: waiter  s: singer  "
             << "t: singing waiter  q: quit\n";
        cin >> choice;
        while (cin.get() != '\n')
        {
            continue;
        }
        while (strchr("wstq", choice) == nullptr)
        {
            cout << "Please enter a w, s, t, or q: ";
            cin >> choice;
            while (cin.get() != '\n')
            {
                continue;
            }
        }
        if (choice == 'q')
        {
            break;
        }
        switch (choice)
        {
        case 'w':
            lolas[ct] = new Waiter;
            break;
        case 's':
            lolas[ct] = new Singer;
            break;
        case 't':
            lolas[ct] = new SingingWaiter;
            break;
        default :
            lolas[ct] = new SingingWaiter;
            break;
        }
        lolas[ct]->Set();
    }

    cout << "\nHere is your staff:\n";
    int i;
    for (i = 0; i < ct; i++)
    {
        lolas[i]->Show();
        cout << endl;
    }
    for (i = 0; i < ct; i++)
    {
        delete lolas[i];
    }
    cout << "Done.\n";

    return 0;
}
